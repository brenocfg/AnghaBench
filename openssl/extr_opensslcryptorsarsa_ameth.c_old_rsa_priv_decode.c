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
struct TYPE_6__ {TYPE_1__* ameth; } ;
struct TYPE_5__ {int /*<<< orphan*/  pkey_id; } ;
typedef  int /*<<< orphan*/  RSA ;
typedef  TYPE_2__ EVP_PKEY ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_RSA_LIB ; 
 int /*<<< orphan*/  EVP_PKEY_assign (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RSA_F_OLD_RSA_PRIV_DECODE ; 
 int /*<<< orphan*/  RSAerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * d2i_RSAPrivateKey (int /*<<< orphan*/ *,unsigned char const**,int) ; 

__attribute__((used)) static int old_rsa_priv_decode(EVP_PKEY *pkey,
                               const unsigned char **pder, int derlen)
{
    RSA *rsa;

    if ((rsa = d2i_RSAPrivateKey(NULL, pder, derlen)) == NULL) {
        RSAerr(RSA_F_OLD_RSA_PRIV_DECODE, ERR_R_RSA_LIB);
        return 0;
    }
    EVP_PKEY_assign(pkey, pkey->ameth->pkey_id, rsa);
    return 1;
}