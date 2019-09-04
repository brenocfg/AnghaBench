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
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 scalar_t__ BIO_do_accept (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_free_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new_accept (char*) ; 
 int /*<<< orphan*/ * BIO_new_ssl (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * BIO_pop (int /*<<< orphan*/ *) ; 
 int BIO_read (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  BIO_set_accept_bios (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CERT_FILE ; 
 int /*<<< orphan*/  ERR_print_errors_fp (int /*<<< orphan*/ ) ; 
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  SSL_CTX_check_private_key (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SSL_CTX_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_CTX_use_PrivateKey_file (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_CTX_use_certificate_chain_file (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_FILETYPE_PEM ; 
 int /*<<< orphan*/  TLS_server_method () ; 
 int /*<<< orphan*/  done ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fwrite (char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  sigsetup () ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 

int main(int argc, char *argv[])
{
    char *port = NULL;
    BIO *in = NULL;
    BIO *ssl_bio, *tmp;
    SSL_CTX *ctx;
    char buf[512];
    int ret = EXIT_FAILURE, i;

    if (argc <= 1)
        port = "*:4433";
    else
        port = argv[1];

    ctx = SSL_CTX_new(TLS_server_method());
    if (!SSL_CTX_use_certificate_chain_file(ctx, CERT_FILE))
        goto err;
    if (!SSL_CTX_use_PrivateKey_file(ctx, CERT_FILE, SSL_FILETYPE_PEM))
        goto err;
    if (!SSL_CTX_check_private_key(ctx))
        goto err;

    /* Setup server side SSL bio */
    ssl_bio = BIO_new_ssl(ctx, 0);

    if ((in = BIO_new_accept(port)) == NULL)
        goto err;

    /*
     * This means that when a new connection is accepted on 'in', The ssl_bio
     * will be 'duplicated' and have the new socket BIO push into it.
     * Basically it means the SSL BIO will be automatically setup
     */
    BIO_set_accept_bios(in, ssl_bio);

    /* Arrange to leave server loop on interrupt */
    sigsetup();

 again:
    /*
     * The first call will setup the accept socket, and the second will get a
     * socket.  In this loop, the first actual accept will occur in the
     * BIO_read() function.
     */

    if (BIO_do_accept(in) <= 0)
        goto err;

    while (!done) {
        i = BIO_read(in, buf, 512);
        if (i == 0) {
            /*
             * If we have finished, remove the underlying BIO stack so the
             * next time we call any function for this BIO, it will attempt
             * to do an accept
             */
            printf("Done\n");
            tmp = BIO_pop(in);
            BIO_free_all(tmp);
            goto again;
        }
        if (i < 0)
            goto err;
        fwrite(buf, 1, i, stdout);
        fflush(stdout);
    }

    ret = EXIT_SUCCESS;
 err:
    if (ret != EXIT_SUCCESS)
        ERR_print_errors_fp(stderr);
    BIO_free(in);
    return ret;
}