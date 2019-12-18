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
struct TYPE_6__ {int dmax; int /*<<< orphan*/ * d; } ;
typedef  int /*<<< orphan*/  BN_ULONG ;
typedef  TYPE_1__ BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/ * bn_expand_internal (TYPE_1__*,int) ; 
 int /*<<< orphan*/  bn_free_d (TYPE_1__*,int) ; 

BIGNUM *bn_expand2(BIGNUM *b, int words)
{
    if (words > b->dmax) {
        BN_ULONG *a = bn_expand_internal(b, words);
        if (!a)
            return NULL;
        if (b->d != NULL)
            bn_free_d(b, 1);
        b->d = a;
        b->dmax = words;
    }

    return b;
}