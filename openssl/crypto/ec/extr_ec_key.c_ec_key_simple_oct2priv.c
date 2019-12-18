#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * priv_key; } ;
typedef  TYPE_1__ EC_KEY ;

/* Variables and functions */
 int /*<<< orphan*/ * BN_bin2bn (unsigned char const*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_secure_new () ; 
 int /*<<< orphan*/  EC_F_EC_KEY_SIMPLE_OCT2PRIV ; 
 int /*<<< orphan*/  ECerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_BN_LIB ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 

int ec_key_simple_oct2priv(EC_KEY *eckey, const unsigned char *buf, size_t len)
{
    if (eckey->priv_key == NULL)
        eckey->priv_key = BN_secure_new();
    if (eckey->priv_key == NULL) {
        ECerr(EC_F_EC_KEY_SIMPLE_OCT2PRIV, ERR_R_MALLOC_FAILURE);
        return 0;
    }
    eckey->priv_key = BN_bin2bn(buf, len, eckey->priv_key);
    if (eckey->priv_key == NULL) {
        ECerr(EC_F_EC_KEY_SIMPLE_OCT2PRIV, ERR_R_BN_LIB);
        return 0;
    }
    return 1;
}