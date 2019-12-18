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
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 scalar_t__ BIO_do_accept (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_free_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new_accept (char*) ; 
 int /*<<< orphan*/ * BIO_new_ssl (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * BIO_pop (int /*<<< orphan*/ *) ; 
 int BIO_read (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  BIO_set_accept_bios (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ BIO_should_retry (int /*<<< orphan*/ *) ; 
 scalar_t__ CONF_modules_load_file (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_print_errors_fp (int /*<<< orphan*/ ) ; 
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 scalar_t__ SSL_CTX_config (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * SSL_CTX_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TLS_server_method () ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fwrite (unsigned char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 

int main(int argc, char *argv[])
{
    unsigned char buf[512];
    char *port = "*:4433";
    BIO *in = NULL;
    BIO *ssl_bio, *tmp;
    SSL_CTX *ctx;
    int ret = EXIT_FAILURE, i;

    ctx = SSL_CTX_new(TLS_server_method());

    if (CONF_modules_load_file("cmod.cnf", "testapp", 0) <= 0) {
        fprintf(stderr, "Error processing config file\n");
        goto err;
    }

    if (SSL_CTX_config(ctx, "server") == 0) {
        fprintf(stderr, "Error configuring server.\n");
        goto err;
    }

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

 again:
    /*
     * The first call will setup the accept socket, and the second will get a
     * socket.  In this loop, the first actual accept will occur in the
     * BIO_read() function.
     */

    if (BIO_do_accept(in) <= 0)
        goto err;

    for (;;) {
        i = BIO_read(in, buf, sizeof(buf));
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
        if (i < 0) {
            if (BIO_should_retry(in))
                continue;
            goto err;
        }
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