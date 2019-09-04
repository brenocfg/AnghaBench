#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * priv_key; } ;
struct TYPE_6__ {TYPE_3__* ec; } ;
struct TYPE_7__ {TYPE_1__ pkey; } ;
typedef  TYPE_2__ EVP_PKEY ;
typedef  TYPE_3__ EC_KEY ;

/* Variables and functions */
 int /*<<< orphan*/  EC_F_EC_PKEY_CHECK ; 
 int EC_KEY_check_key (TYPE_3__*) ; 
 int /*<<< orphan*/  EC_R_MISSING_PRIVATE_KEY ; 
 int /*<<< orphan*/  ECerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ec_pkey_check(const EVP_PKEY *pkey)
{
    EC_KEY *eckey = pkey->pkey.ec;

    /* stay consistent to what EVP_PKEY_check demands */
    if (eckey->priv_key == NULL) {
        ECerr(EC_F_EC_PKEY_CHECK, EC_R_MISSING_PRIVATE_KEY);
        return 0;
    }

    return EC_KEY_check_key(eckey);
}