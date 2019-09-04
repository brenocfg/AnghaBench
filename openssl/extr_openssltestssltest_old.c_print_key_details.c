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
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  EC_KEY ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char const*) ; 
 int EC_GROUP_get_curve_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EC_KEY_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_KEY_get0_group (int /*<<< orphan*/ *) ; 
 char* EC_curve_nid2nist (int) ; 
#define  EVP_PKEY_DH 130 
#define  EVP_PKEY_DSA 129 
 int EVP_PKEY_EC ; 
#define  EVP_PKEY_RSA 128 
 int /*<<< orphan*/  EVP_PKEY_bits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_PKEY_get1_EC_KEY (int /*<<< orphan*/ *) ; 
 int EVP_PKEY_id (int /*<<< orphan*/ *) ; 
 char* OBJ_nid2sn (int) ; 

__attribute__((used)) static void print_key_details(BIO *out, EVP_PKEY *key)
{
    int keyid = EVP_PKEY_id(key);
#ifndef OPENSSL_NO_EC
    if (keyid == EVP_PKEY_EC) {
        EC_KEY *ec = EVP_PKEY_get1_EC_KEY(key);
        int nid;
        const char *cname;
        nid = EC_GROUP_get_curve_name(EC_KEY_get0_group(ec));
        EC_KEY_free(ec);
        cname = EC_curve_nid2nist(nid);
        if (!cname)
            cname = OBJ_nid2sn(nid);
        BIO_printf(out, "%d bits EC (%s)", EVP_PKEY_bits(key), cname);
    } else
#endif
    {
        const char *algname;
        switch (keyid) {
        case EVP_PKEY_RSA:
            algname = "RSA";
            break;
        case EVP_PKEY_DSA:
            algname = "DSA";
            break;
        case EVP_PKEY_DH:
            algname = "DH";
            break;
        default:
            algname = OBJ_nid2sn(keyid);
            break;
        }
        BIO_printf(out, "%d bits %s", EVP_PKEY_bits(key), algname);
    }
}