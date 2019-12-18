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
struct TYPE_3__ {int /*<<< orphan*/ * mont_data; int /*<<< orphan*/  order; int /*<<< orphan*/  libctx; } ;
typedef  TYPE_1__ EC_GROUP ;
typedef  int /*<<< orphan*/  BN_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_new_ex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_MONT_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_MONT_CTX_new () ; 
 int /*<<< orphan*/  BN_MONT_CTX_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ec_precompute_mont_data(EC_GROUP *group)
{
    BN_CTX *ctx = BN_CTX_new_ex(group->libctx);
    int ret = 0;

    BN_MONT_CTX_free(group->mont_data);
    group->mont_data = NULL;

    if (ctx == NULL)
        goto err;

    group->mont_data = BN_MONT_CTX_new();
    if (group->mont_data == NULL)
        goto err;

    if (!BN_MONT_CTX_set(group->mont_data, group->order, ctx)) {
        BN_MONT_CTX_free(group->mont_data);
        group->mont_data = NULL;
        goto err;
    }

    ret = 1;

 err:

    BN_CTX_free(ctx);
    return ret;
}