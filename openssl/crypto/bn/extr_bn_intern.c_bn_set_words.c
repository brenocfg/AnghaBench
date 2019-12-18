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
struct TYPE_5__ {int top; int /*<<< orphan*/  d; } ;
typedef  int /*<<< orphan*/  BN_ULONG ;
typedef  TYPE_1__ BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_F_BN_SET_WORDS ; 
 int /*<<< orphan*/  BNerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  bn_correct_top (TYPE_1__*) ; 
 int /*<<< orphan*/ * bn_wexpand (TYPE_1__*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 

int bn_set_words(BIGNUM *a, const BN_ULONG *words, int num_words)
{
    if (bn_wexpand(a, num_words) == NULL) {
        BNerr(BN_F_BN_SET_WORDS, ERR_R_MALLOC_FAILURE);
        return 0;
    }

    memcpy(a->d, words, sizeof(BN_ULONG) * num_words);
    a->top = num_words;
    bn_correct_top(a);
    return 1;
}