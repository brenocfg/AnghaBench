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
typedef  int /*<<< orphan*/  X509 ;
typedef  int /*<<< orphan*/  SSL ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new_file (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * PEM_read_bio_PrivateKey (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PEM_read_bio_X509 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SSL_get_peer_certificate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cert ; 
 int /*<<< orphan*/  privkey ; 

__attribute__((used)) static int client_cert_cb(SSL *ssl, X509 **x509, EVP_PKEY **pkey)
{
    X509 *xcert, *peer;
    EVP_PKEY *privpkey;
    BIO *in = NULL;

    /* Check that SSL_get_peer_certificate() returns something sensible */
    peer = SSL_get_peer_certificate(ssl);
    if (!TEST_ptr(peer))
        return 0;
    X509_free(peer);

    in = BIO_new_file(cert, "r");
    if (!TEST_ptr(in))
        return 0;

    xcert = PEM_read_bio_X509(in, NULL, NULL, NULL);
    BIO_free(in);
    if (!TEST_ptr(xcert))
        return 0;

    in = BIO_new_file(privkey, "r");
    if (!TEST_ptr(in)) {
        X509_free(xcert);
        return 0;
    }

    privpkey = PEM_read_bio_PrivateKey(in, NULL, NULL, NULL);
    BIO_free(in);
    if (!TEST_ptr(privpkey)) {
        X509_free(xcert);
        return 0;
    }

    *x509 = xcert;
    *pkey = privpkey;

    return 1;
}