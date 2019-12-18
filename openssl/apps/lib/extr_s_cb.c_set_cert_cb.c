#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {struct TYPE_2__* prev; int /*<<< orphan*/ * chain; scalar_t__ build_chain; int /*<<< orphan*/  key; int /*<<< orphan*/  cert; struct TYPE_2__* next; } ;
typedef  TYPE_1__ SSL_EXCERT ;
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  BIO_puts (int /*<<< orphan*/ ,char*) ; 
 int CERT_PKEY_VALID ; 
 int /*<<< orphan*/  SSL_build_cert_chain (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_certs_clear (int /*<<< orphan*/ *) ; 
 int SSL_check_chain (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_set1_chain (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_use_PrivateKey (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_use_certificate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_NAME_print_ex (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_get_subject_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_err ; 
 int /*<<< orphan*/  get_nameopt () ; 
 int /*<<< orphan*/  print_chain_flags (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int set_cert_cb(SSL *ssl, void *arg)
{
    int i, rv;
    SSL_EXCERT *exc = arg;
#ifdef CERT_CB_TEST_RETRY
    static int retry_cnt;
    if (retry_cnt < 5) {
        retry_cnt++;
        BIO_printf(bio_err,
                   "Certificate callback retry test: count %d\n",
                   retry_cnt);
        return -1;
    }
#endif
    SSL_certs_clear(ssl);

    if (exc == NULL)
        return 1;

    /*
     * Go to end of list and traverse backwards since we prepend newer
     * entries this retains the original order.
     */
    while (exc->next != NULL)
        exc = exc->next;

    i = 0;

    while (exc != NULL) {
        i++;
        rv = SSL_check_chain(ssl, exc->cert, exc->key, exc->chain);
        BIO_printf(bio_err, "Checking cert chain %d:\nSubject: ", i);
        X509_NAME_print_ex(bio_err, X509_get_subject_name(exc->cert), 0,
                           get_nameopt());
        BIO_puts(bio_err, "\n");
        print_chain_flags(ssl, rv);
        if (rv & CERT_PKEY_VALID) {
            if (!SSL_use_certificate(ssl, exc->cert)
                    || !SSL_use_PrivateKey(ssl, exc->key)) {
                return 0;
            }
            /*
             * NB: we wouldn't normally do this as it is not efficient
             * building chains on each connection better to cache the chain
             * in advance.
             */
            if (exc->build_chain) {
                if (!SSL_build_cert_chain(ssl, 0))
                    return 0;
            } else if (exc->chain != NULL) {
                SSL_set1_chain(ssl, exc->chain);
            }
        }
        exc = exc->prev;
    }
    return 1;
}