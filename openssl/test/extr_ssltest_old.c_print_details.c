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
typedef  int /*<<< orphan*/  SSL_CIPHER ;
typedef  int /*<<< orphan*/  SSL ;
typedef  int /*<<< orphan*/  EVP_PKEY ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  BIO_puts (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OBJ_nid2sn (int) ; 
 int /*<<< orphan*/  SSL_CIPHER_get_name (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  SSL_CIPHER_get_version (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * SSL_get_current_cipher (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SSL_get_peer_certificate (int /*<<< orphan*/ *) ; 
 scalar_t__ SSL_get_peer_signature_nid (int /*<<< orphan*/ *,int*) ; 
 scalar_t__ SSL_get_peer_tmp_key (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  SSL_get_version (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * X509_get0_pubkey (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bio_stdout ; 
 int /*<<< orphan*/  print_key_details (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void print_details(SSL *c_ssl, const char *prefix)
{
    const SSL_CIPHER *ciph;
    int mdnid;
    X509 *cert;
    EVP_PKEY *pkey;

    ciph = SSL_get_current_cipher(c_ssl);
    BIO_printf(bio_stdout, "%s%s, cipher %s %s",
               prefix,
               SSL_get_version(c_ssl),
               SSL_CIPHER_get_version(ciph), SSL_CIPHER_get_name(ciph));
    cert = SSL_get_peer_certificate(c_ssl);
    if (cert != NULL) {
        EVP_PKEY* pubkey = X509_get0_pubkey(cert);

        if (pubkey != NULL) {
            BIO_puts(bio_stdout, ", ");
            print_key_details(bio_stdout, pubkey);
        }
        X509_free(cert);
    }
    if (SSL_get_peer_tmp_key(c_ssl, &pkey)) {
        BIO_puts(bio_stdout, ", temp key: ");
        print_key_details(bio_stdout, pkey);
        EVP_PKEY_free(pkey);
    }
    if (SSL_get_peer_signature_nid(c_ssl, &mdnid))
        BIO_printf(bio_stdout, ", digest=%s", OBJ_nid2sn(mdnid));
    BIO_printf(bio_stdout, "\n");
}