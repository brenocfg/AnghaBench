#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * field_data1; int /*<<< orphan*/ * field_data2; } ;
typedef  TYPE_1__ EC_GROUP ;

/* Variables and functions */
 int /*<<< orphan*/  BN_MONT_CTX_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_MONT_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_MONT_CTX_new () ; 
 int /*<<< orphan*/  BN_clear_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_dup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ec_GFp_simple_group_copy (TYPE_1__*,TYPE_1__ const*) ; 

int ec_GFp_mont_group_copy(EC_GROUP *dest, const EC_GROUP *src)
{
    BN_MONT_CTX_free(dest->field_data1);
    dest->field_data1 = NULL;
    BN_clear_free(dest->field_data2);
    dest->field_data2 = NULL;

    if (!ec_GFp_simple_group_copy(dest, src))
        return 0;

    if (src->field_data1 != NULL) {
        dest->field_data1 = BN_MONT_CTX_new();
        if (dest->field_data1 == NULL)
            return 0;
        if (!BN_MONT_CTX_copy(dest->field_data1, src->field_data1))
            goto err;
    }
    if (src->field_data2 != NULL) {
        dest->field_data2 = BN_dup(src->field_data2);
        if (dest->field_data2 == NULL)
            goto err;
    }

    return 1;

 err:
    BN_MONT_CTX_free(dest->field_data1);
    dest->field_data1 = NULL;
    return 0;
}