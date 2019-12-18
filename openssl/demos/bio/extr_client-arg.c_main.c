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
typedef  int /*<<< orphan*/  SSL_CTX ;
typedef  int /*<<< orphan*/  SSL_CONF_CTX ;
typedef  int /*<<< orphan*/  SSL ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_NOCLOSE ; 
 scalar_t__ BIO_do_connect (int /*<<< orphan*/ *) ; 
 scalar_t__ BIO_do_handshake (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_free_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_get_ssl (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * BIO_new_fp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * BIO_new_ssl_connect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_puts (int /*<<< orphan*/ *,char*) ; 
 int BIO_read (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  BIO_set_conn_hostname (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  BIO_write (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  ERR_print_errors_fp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_CONF_CTX_finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_CONF_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SSL_CONF_CTX_new () ; 
 int /*<<< orphan*/  SSL_CONF_CTX_set_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_CONF_CTX_set_ssl_ctx (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_CONF_FLAG_CLIENT ; 
 int SSL_CONF_cmd_argv (int /*<<< orphan*/ *,int*,char***) ; 
 int /*<<< orphan*/ * SSL_CTX_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_MODE_AUTO_RETRY ; 
 int /*<<< orphan*/  SSL_set_mode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TLS_client_method () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ strcmp (char*,char*) ; 

int main(int argc, char **argv)
{
    BIO *sbio = NULL, *out = NULL;
    int len;
    char tmpbuf[1024];
    SSL_CTX *ctx;
    SSL_CONF_CTX *cctx;
    SSL *ssl;
    char **args = argv + 1;
    const char *connect_str = "localhost:4433";
    int nargs = argc - 1;

    ctx = SSL_CTX_new(TLS_client_method());
    cctx = SSL_CONF_CTX_new();
    SSL_CONF_CTX_set_flags(cctx, SSL_CONF_FLAG_CLIENT);
    SSL_CONF_CTX_set_ssl_ctx(cctx, ctx);
    while (*args && **args == '-') {
        int rv;
        /* Parse standard arguments */
        rv = SSL_CONF_cmd_argv(cctx, &nargs, &args);
        if (rv == -3) {
            fprintf(stderr, "Missing argument for %s\n", *args);
            goto end;
        }
        if (rv < 0) {
            fprintf(stderr, "Error in command %s\n", *args);
            ERR_print_errors_fp(stderr);
            goto end;
        }
        /* If rv > 0 we processed something so proceed to next arg */
        if (rv > 0)
            continue;
        /* Otherwise application specific argument processing */
        if (strcmp(*args, "-connect") == 0) {
            connect_str = args[1];
            if (connect_str == NULL) {
                fprintf(stderr, "Missing -connect argument\n");
                goto end;
            }
            args += 2;
            nargs -= 2;
            continue;
        } else {
            fprintf(stderr, "Unknown argument %s\n", *args);
            goto end;
        }
    }

    if (!SSL_CONF_CTX_finish(cctx)) {
        fprintf(stderr, "Finish error\n");
        ERR_print_errors_fp(stderr);
        goto end;
    }

    /*
     * We'd normally set some stuff like the verify paths and * mode here
     * because as things stand this will connect to * any server whose
     * certificate is signed by any CA.
     */

    sbio = BIO_new_ssl_connect(ctx);

    BIO_get_ssl(sbio, &ssl);

    if (!ssl) {
        fprintf(stderr, "Can't locate SSL pointer\n");
        goto end;
    }

    /* Don't want any retries */
    SSL_set_mode(ssl, SSL_MODE_AUTO_RETRY);

    /* We might want to do other things with ssl here */

    BIO_set_conn_hostname(sbio, connect_str);

    out = BIO_new_fp(stdout, BIO_NOCLOSE);
    if (BIO_do_connect(sbio) <= 0) {
        fprintf(stderr, "Error connecting to server\n");
        ERR_print_errors_fp(stderr);
        goto end;
    }

    if (BIO_do_handshake(sbio) <= 0) {
        fprintf(stderr, "Error establishing SSL connection\n");
        ERR_print_errors_fp(stderr);
        goto end;
    }

    /* Could examine ssl here to get connection info */

    BIO_puts(sbio, "GET / HTTP/1.0\n\n");
    for (;;) {
        len = BIO_read(sbio, tmpbuf, 1024);
        if (len <= 0)
            break;
        BIO_write(out, tmpbuf, len);
    }
 end:
    SSL_CONF_CTX_free(cctx);
    BIO_free_all(sbio);
    BIO_free(out);
    return 0;
}