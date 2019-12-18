#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509_ALGOR ;
struct TYPE_6__ {TYPE_1__* ameth; } ;
struct TYPE_5__ {int /*<<< orphan*/  pkey_id; } ;
typedef  int /*<<< orphan*/  RSA ;
typedef  int /*<<< orphan*/  PKCS8_PRIV_KEY_INFO ;
typedef  TYPE_2__ EVP_PKEY ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_RSA_LIB ; 
 int /*<<< orphan*/  EVP_PKEY_assign (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PKCS8_pkey_get0 (int /*<<< orphan*/ *,unsigned char const**,int*,int /*<<< orphan*/  const**,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  RSA_F_RSA_PRIV_DECODE ; 
 int /*<<< orphan*/  RSA_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RSAerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * d2i_RSAPrivateKey (int /*<<< orphan*/ *,unsigned char const**,int) ; 
 int /*<<< orphan*/  rsa_param_decode (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int rsa_priv_decode(EVP_PKEY *pkey, const PKCS8_PRIV_KEY_INFO *p8)
{
    const unsigned char *p;
    RSA *rsa;
    int pklen;
    const X509_ALGOR *alg;

    if (!PKCS8_pkey_get0(NULL, &p, &pklen, &alg, p8))
        return 0;
    rsa = d2i_RSAPrivateKey(NULL, &p, pklen);
    if (rsa == NULL) {
        RSAerr(RSA_F_RSA_PRIV_DECODE, ERR_R_RSA_LIB);
        return 0;
    }
    if (!rsa_param_decode(rsa, alg)) {
        RSA_free(rsa);
        return 0;
    }
    EVP_PKEY_assign(pkey, pkey->ameth->pkey_id, rsa);
    return 1;
}