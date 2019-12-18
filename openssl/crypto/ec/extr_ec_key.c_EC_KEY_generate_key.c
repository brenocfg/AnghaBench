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
struct TYPE_6__ {TYPE_1__* meth; int /*<<< orphan*/ * group; } ;
struct TYPE_5__ {int (* keygen ) (TYPE_2__*) ;} ;
typedef  TYPE_2__ EC_KEY ;

/* Variables and functions */
 int /*<<< orphan*/  EC_F_EC_KEY_GENERATE_KEY ; 
 int /*<<< orphan*/  EC_R_OPERATION_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ECerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_PASSED_NULL_PARAMETER ; 
 int stub1 (TYPE_2__*) ; 

int EC_KEY_generate_key(EC_KEY *eckey)
{
    if (eckey == NULL || eckey->group == NULL) {
        ECerr(EC_F_EC_KEY_GENERATE_KEY, ERR_R_PASSED_NULL_PARAMETER);
        return 0;
    }
    if (eckey->meth->keygen != NULL)
        return eckey->meth->keygen(eckey);
    ECerr(EC_F_EC_KEY_GENERATE_KEY, EC_R_OPERATION_NOT_SUPPORTED);
    return 0;
}