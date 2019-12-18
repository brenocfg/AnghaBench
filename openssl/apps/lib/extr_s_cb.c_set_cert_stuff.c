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

/* Variables and functions */
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ERR_print_errors (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_CTX_check_private_key (int /*<<< orphan*/ *) ; 
 scalar_t__ SSL_CTX_use_PrivateKey_file (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ SSL_CTX_use_certificate_file (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_FILETYPE_PEM ; 
 int /*<<< orphan*/  bio_err ; 

int set_cert_stuff(SSL_CTX *ctx, char *cert_file, char *key_file)
{
    if (cert_file != NULL) {
        if (SSL_CTX_use_certificate_file(ctx, cert_file,
                                         SSL_FILETYPE_PEM) <= 0) {
            BIO_printf(bio_err, "unable to get certificate from '%s'\n",
                       cert_file);
            ERR_print_errors(bio_err);
            return 0;
        }
        if (key_file == NULL)
            key_file = cert_file;
        if (SSL_CTX_use_PrivateKey_file(ctx, key_file, SSL_FILETYPE_PEM) <= 0) {
            BIO_printf(bio_err, "unable to get private key from '%s'\n",
                       key_file);
            ERR_print_errors(bio_err);
            return 0;
        }

        /*
         * If we are using DSA, we can copy the parameters from the private
         * key
         */

        /*
         * Now we know that a key and cert have been set against the SSL
         * context
         */
        if (!SSL_CTX_check_private_key(ctx)) {
            BIO_printf(bio_err,
                       "Private key does not match the certificate public key\n");
            return 0;
        }
    }
    return 1;
}