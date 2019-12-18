#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  SSL_CTX ;
typedef  int /*<<< orphan*/  SSL ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_CLOSE ; 
 int /*<<< orphan*/  BIO_f_ssl () ; 
 int /*<<< orphan*/  BIO_free_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * BIO_push (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int BIO_read (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  BIO_s_connect () ; 
 int /*<<< orphan*/  BIO_set_conn_hostname (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  BIO_set_nbio (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  BIO_set_ssl (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ BIO_should_retry (int /*<<< orphan*/ *) ; 
 int BIO_write (int /*<<< orphan*/ *,char*,int) ; 
 char* CAFILE ; 
 scalar_t__ ERR_peek_error () ; 
 int /*<<< orphan*/  ERR_print_errors_fp (int /*<<< orphan*/ ) ; 
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 char* HOSTPORT ; 
 char* OPENSSL_strdup (char const*) ; 
 int /*<<< orphan*/  SSL_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_CTX_load_verify_locations (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SSL_CTX_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_CTX_set_verify (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_VERIFY_PEER ; 
 int /*<<< orphan*/ * SSL_new (int /*<<< orphan*/ *) ; 
 scalar_t__ SSL_set1_host (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  SSL_set_connect_state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TLS_client_method () ; 
 int /*<<< orphan*/  dbug_init () ; 
 int errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  fwrite (char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  sock_init () ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 char* strchr (char*,char) ; 
 int strlen (char*) ; 

int main(int argc, char *argv[])
{
    const char *hostport = HOSTPORT;
    const char *CAfile = CAFILE;
    char *hostname;
    char *cp;
    BIO *out = NULL;
    char buf[1024 * 10], *p;
    SSL_CTX *ssl_ctx = NULL;
    SSL *ssl;
    BIO *ssl_bio;
    int i, len, off, ret = EXIT_FAILURE;

    if (argc > 1)
        hostport = argv[1];
    if (argc > 2)
        CAfile = argv[2];

    hostname = OPENSSL_strdup(hostport);
    if ((cp = strchr(hostname, ':')) != NULL)
        *cp = 0;

#ifdef WATT32
    dbug_init();
    sock_init();
#endif

    ssl_ctx = SSL_CTX_new(TLS_client_method());

    /* Enable trust chain verification */
    SSL_CTX_set_verify(ssl_ctx, SSL_VERIFY_PEER, NULL);
    SSL_CTX_load_verify_locations(ssl_ctx, CAfile, NULL);

    /* Lets make a SSL structure */
    ssl = SSL_new(ssl_ctx);
    SSL_set_connect_state(ssl);

    /* Enable peername verification */
    if (SSL_set1_host(ssl, hostname) <= 0)
        goto err;

    /* Use it inside an SSL BIO */
    ssl_bio = BIO_new(BIO_f_ssl());
    BIO_set_ssl(ssl_bio, ssl, BIO_CLOSE);

    /* Lets use a connect BIO under the SSL BIO */
    out = BIO_new(BIO_s_connect());
    BIO_set_conn_hostname(out, hostport);
    BIO_set_nbio(out, 1);
    out = BIO_push(ssl_bio, out);

    p = "GET / HTTP/1.0\r\n\r\n";
    len = strlen(p);

    off = 0;
    for (;;) {
        i = BIO_write(out, &(p[off]), len);
        if (i <= 0) {
            if (BIO_should_retry(out)) {
                fprintf(stderr, "write DELAY\n");
                sleep(1);
                continue;
            } else {
                goto err;
            }
        }
        off += i;
        len -= i;
        if (len <= 0)
            break;
    }

    for (;;) {
        i = BIO_read(out, buf, sizeof(buf));
        if (i == 0)
            break;
        if (i < 0) {
            if (BIO_should_retry(out)) {
                fprintf(stderr, "read DELAY\n");
                sleep(1);
                continue;
            }
            goto err;
        }
        fwrite(buf, 1, i, stdout);
    }

    ret = EXIT_SUCCESS;
    goto done;

 err:
    if (ERR_peek_error() == 0) { /* system call error */
        fprintf(stderr, "errno=%d ", errno);
        perror("error");
    } else {
        ERR_print_errors_fp(stderr);
    }
 done:
    BIO_free_all(out);
    SSL_CTX_free(ssl_ctx);
    return ret;
}