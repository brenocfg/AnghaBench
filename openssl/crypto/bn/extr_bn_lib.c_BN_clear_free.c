#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * d; } ;
typedef  TYPE_1__ BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_FLG_MALLOCED ; 
 int /*<<< orphan*/  BN_FLG_STATIC_DATA ; 
 scalar_t__ BN_get_flags (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_cleanse (TYPE_1__*,int) ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 int /*<<< orphan*/  bn_free_d (TYPE_1__*,int) ; 

void BN_clear_free(BIGNUM *a)
{
    if (a == NULL)
        return;
    if (a->d != NULL && !BN_get_flags(a, BN_FLG_STATIC_DATA))
        bn_free_d(a, 1);
    if (BN_get_flags(a, BN_FLG_MALLOCED)) {
        OPENSSL_cleanse(a, sizeof(*a));
        OPENSSL_free(a);
    }
}