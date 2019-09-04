#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * group; } ;
struct TYPE_5__ {TYPE_3__* ec; } ;
struct TYPE_6__ {TYPE_1__ pkey; } ;
typedef  TYPE_2__ EVP_PKEY ;
typedef  TYPE_3__ EC_KEY ;

/* Variables and functions */
 int /*<<< orphan*/  EC_F_EC_PKEY_PARAM_CHECK ; 
 int EC_GROUP_check (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_R_MISSING_PARAMETERS ; 
 int /*<<< orphan*/  ECerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ec_pkey_param_check(const EVP_PKEY *pkey)
{
    EC_KEY *eckey = pkey->pkey.ec;

    /* stay consistent to what EVP_PKEY_check demands */
    if (eckey->group == NULL) {
        ECerr(EC_F_EC_PKEY_PARAM_CHECK, EC_R_MISSING_PARAMETERS);
        return 0;
    }

    return EC_GROUP_check(eckey->group, NULL);
}