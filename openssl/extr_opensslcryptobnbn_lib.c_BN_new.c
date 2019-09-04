#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_FLG_MALLOCED ; 
 int /*<<< orphan*/  BN_F_BN_NEW ; 
 int /*<<< orphan*/  BNerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 TYPE_1__* OPENSSL_zalloc (int) ; 
 int /*<<< orphan*/  bn_check_top (TYPE_1__*) ; 

BIGNUM *BN_new(void)
{
    BIGNUM *ret;

    if ((ret = OPENSSL_zalloc(sizeof(*ret))) == NULL) {
        BNerr(BN_F_BN_NEW, ERR_R_MALLOC_FAILURE);
        return NULL;
    }
    ret->flags = BN_FLG_MALLOCED;
    bn_check_top(ret);
    return ret;
}