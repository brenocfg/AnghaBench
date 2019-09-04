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
typedef  int /*<<< orphan*/  SSL ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  EC_KEY ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ *,char*,char const*,...) ; 
 int /*<<< orphan*/  BIO_puts (int /*<<< orphan*/ *,char*) ; 
 int EC_GROUP_get_curve_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EC_KEY_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_KEY_get0_group (int /*<<< orphan*/ *) ; 
 char* EC_curve_nid2nist (int) ; 
#define  EVP_PKEY_DH 130 
#define  EVP_PKEY_EC 129 
#define  EVP_PKEY_RSA 128 
 int /*<<< orphan*/  EVP_PKEY_bits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_PKEY_get1_EC_KEY (int /*<<< orphan*/ *) ; 
 int EVP_PKEY_id (int /*<<< orphan*/ *) ; 
 char const* OBJ_nid2sn (int) ; 
 int /*<<< orphan*/  SSL_get_peer_tmp_key (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 

int ssl_print_tmp_key(BIO *out, SSL *s)
{
    EVP_PKEY *key;

    if (!SSL_get_peer_tmp_key(s, &key))
        return 1;
    BIO_puts(out, "Server Temp Key: ");
    switch (EVP_PKEY_id(key)) {
    case EVP_PKEY_RSA:
        BIO_printf(out, "RSA, %d bits\n", EVP_PKEY_bits(key));
        break;

    case EVP_PKEY_DH:
        BIO_printf(out, "DH, %d bits\n", EVP_PKEY_bits(key));
        break;
#ifndef OPENSSL_NO_EC
    case EVP_PKEY_EC:
        {
            EC_KEY *ec = EVP_PKEY_get1_EC_KEY(key);
            int nid;
            const char *cname;
            nid = EC_GROUP_get_curve_name(EC_KEY_get0_group(ec));
            EC_KEY_free(ec);
            cname = EC_curve_nid2nist(nid);
            if (cname == NULL)
                cname = OBJ_nid2sn(nid);
            BIO_printf(out, "ECDH, %s, %d bits\n", cname, EVP_PKEY_bits(key));
        }
    break;
#endif
    default:
        BIO_printf(out, "%s, %d bits\n", OBJ_nid2sn(EVP_PKEY_id(key)),
                   EVP_PKEY_bits(key));
    }
    EVP_PKEY_free(key);
    return 1;
}