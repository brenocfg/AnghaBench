#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  dirty_cnt; } ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  TYPE_1__ DSA ;

/* Variables and functions */
 int /*<<< orphan*/  DSA_F_OLD_DSA_PRIV_DECODE ; 
 int /*<<< orphan*/  DSAerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_DSA_LIB ; 
 int /*<<< orphan*/  EVP_PKEY_assign_DSA (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* d2i_DSAPrivateKey (int /*<<< orphan*/ *,unsigned char const**,int) ; 

__attribute__((used)) static int old_dsa_priv_decode(EVP_PKEY *pkey,
                               const unsigned char **pder, int derlen)
{
    DSA *dsa;

    if ((dsa = d2i_DSAPrivateKey(NULL, pder, derlen)) == NULL) {
        DSAerr(DSA_F_OLD_DSA_PRIV_DECODE, ERR_R_DSA_LIB);
        return 0;
    }
    dsa->dirty_cnt++;
    EVP_PKEY_assign_DSA(pkey, dsa);
    return 1;
}