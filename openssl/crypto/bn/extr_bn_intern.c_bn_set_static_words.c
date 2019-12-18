#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int dmax; int top; int /*<<< orphan*/  flags; scalar_t__ neg; int /*<<< orphan*/ * d; } ;
typedef  int /*<<< orphan*/  BN_ULONG ;
typedef  TYPE_1__ BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_FLG_STATIC_DATA ; 
 int /*<<< orphan*/  bn_correct_top (TYPE_1__*) ; 

void bn_set_static_words(BIGNUM *a, const BN_ULONG *words, int size)
{
    /*
     * |const| qualifier omission is compensated by BN_FLG_STATIC_DATA
     * flag, which effectively means "read-only data".
     */
    a->d = (BN_ULONG *)words;
    a->dmax = a->top = size;
    a->neg = 0;
    a->flags |= BN_FLG_STATIC_DATA;
    bn_correct_top(a);
}