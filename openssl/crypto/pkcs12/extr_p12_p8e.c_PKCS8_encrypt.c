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
typedef  int /*<<< orphan*/  X509_SIG ;
typedef  int /*<<< orphan*/  X509_ALGOR ;
typedef  int /*<<< orphan*/  PKCS8_PRIV_KEY_INFO ;
typedef  int /*<<< orphan*/  EVP_CIPHER ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_ASN1_LIB ; 
 int /*<<< orphan*/  ERR_clear_error () ; 
 int /*<<< orphan*/  EVP_PBE_TYPE_PRF ; 
 scalar_t__ EVP_PBE_find (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PKCS12_F_PKCS8_ENCRYPT ; 
 int /*<<< orphan*/  PKCS12err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * PKCS5_pbe2_set (int /*<<< orphan*/  const*,int,unsigned char*,int) ; 
 int /*<<< orphan*/ * PKCS5_pbe2_set_iv (int /*<<< orphan*/  const*,int,unsigned char*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * PKCS5_pbe_set (int,int,unsigned char*,int) ; 
 int /*<<< orphan*/ * PKCS8_set0_pbe (char const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_ALGOR_free (int /*<<< orphan*/ *) ; 

X509_SIG *PKCS8_encrypt(int pbe_nid, const EVP_CIPHER *cipher,
                        const char *pass, int passlen,
                        unsigned char *salt, int saltlen, int iter,
                        PKCS8_PRIV_KEY_INFO *p8inf)
{
    X509_SIG *p8 = NULL;
    X509_ALGOR *pbe;

    if (pbe_nid == -1)
        pbe = PKCS5_pbe2_set(cipher, iter, salt, saltlen);
    else if (EVP_PBE_find(EVP_PBE_TYPE_PRF, pbe_nid, NULL, NULL, 0))
        pbe = PKCS5_pbe2_set_iv(cipher, iter, salt, saltlen, NULL, pbe_nid);
    else {
        ERR_clear_error();
        pbe = PKCS5_pbe_set(pbe_nid, iter, salt, saltlen);
    }
    if (pbe == NULL) {
        PKCS12err(PKCS12_F_PKCS8_ENCRYPT, ERR_R_ASN1_LIB);
        return NULL;
    }
    p8 = PKCS8_set0_pbe(pass, passlen, p8inf, pbe);
    if (p8 == NULL) {
        X509_ALGOR_free(pbe);
        return NULL;
    }

    return p8;
}