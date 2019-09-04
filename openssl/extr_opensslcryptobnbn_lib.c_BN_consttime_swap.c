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
struct TYPE_5__ {int top; int neg; int flags; int* d; } ;
typedef  int BN_ULONG ;
typedef  TYPE_1__ BIGNUM ;

/* Variables and functions */
 int BN_BITS2 ; 
 int BN_FLG_CONSTTIME ; 
 int BN_FLG_FIXED_TOP ; 
 int /*<<< orphan*/  bn_wcheck_size (TYPE_1__*,int) ; 

void BN_consttime_swap(BN_ULONG condition, BIGNUM *a, BIGNUM *b, int nwords)
{
    BN_ULONG t;
    int i;

    if (a == b)
        return;

    bn_wcheck_size(a, nwords);
    bn_wcheck_size(b, nwords);

    condition = ((~condition & ((condition - 1))) >> (BN_BITS2 - 1)) - 1;

    t = (a->top ^ b->top) & condition;
    a->top ^= t;
    b->top ^= t;

    t = (a->neg ^ b->neg) & condition;
    a->neg ^= t;
    b->neg ^= t;

    /*-
     * BN_FLG_STATIC_DATA: indicates that data may not be written to. Intention
     * is actually to treat it as it's read-only data, and some (if not most)
     * of it does reside in read-only segment. In other words observation of
     * BN_FLG_STATIC_DATA in BN_consttime_swap should be treated as fatal
     * condition. It would either cause SEGV or effectively cause data
     * corruption.
     *
     * BN_FLG_MALLOCED: refers to BN structure itself, and hence must be
     * preserved.
     *
     * BN_FLG_SECURE: must be preserved, because it determines how x->d was
     * allocated and hence how to free it.
     *
     * BN_FLG_CONSTTIME: sufficient to mask and swap
     *
     * BN_FLG_FIXED_TOP: indicates that we haven't called bn_correct_top() on
     * the data, so the d array may be padded with additional 0 values (i.e.
     * top could be greater than the minimal value that it could be). We should
     * be swapping it
     */

#define BN_CONSTTIME_SWAP_FLAGS (BN_FLG_CONSTTIME | BN_FLG_FIXED_TOP)

    t = ((a->flags ^ b->flags) & BN_CONSTTIME_SWAP_FLAGS) & condition;
    a->flags ^= t;
    b->flags ^= t;

    /* conditionally swap the data */
    for (i = 0; i < nwords; i++) {
        t = (a->d[i] ^ b->d[i]) & condition;
        a->d[i] ^= t;
        b->d[i] ^= t;
    }
}