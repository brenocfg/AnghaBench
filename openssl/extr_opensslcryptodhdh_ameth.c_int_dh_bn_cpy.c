#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_FLG_MALLOCED ; 
 int /*<<< orphan*/  BN_FLG_STATIC_DATA ; 
 int /*<<< orphan*/  BN_clear_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_dup (int /*<<< orphan*/  const*) ; 
 scalar_t__ BN_get_flags (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int int_dh_bn_cpy(BIGNUM **dst, const BIGNUM *src)
{
    BIGNUM *a;

    /*
     * If source is read only just copy the pointer, so
     * we don't have to reallocate it.
     */
    if (src == NULL)
        a = NULL;
    else if (BN_get_flags(src, BN_FLG_STATIC_DATA)
                && !BN_get_flags(src, BN_FLG_MALLOCED))
        a = (BIGNUM *)src;
    else if ((a = BN_dup(src)) == NULL)
        return 0;
    BN_clear_free(*dst);
    *dst = a;
    return 1;
}