#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ top; int neg; } ;
typedef  int BN_ULONG ;
typedef  TYPE_1__ BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_DEC_CONV ; 
 int BN_DEC_NUM ; 
 int /*<<< orphan*/  BN_add_word (TYPE_1__*,int) ; 
 int /*<<< orphan*/  BN_free (TYPE_1__*) ; 
 int /*<<< orphan*/  BN_mul_word (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* BN_new () ; 
 int /*<<< orphan*/  BN_zero (TYPE_1__*) ; 
 int INT_MAX ; 
 int /*<<< orphan*/  bn_check_top (TYPE_1__*) ; 
 int /*<<< orphan*/  bn_correct_top (TYPE_1__*) ; 
 int /*<<< orphan*/ * bn_expand (TYPE_1__*,int) ; 
 scalar_t__ ossl_isdigit (char const) ; 

int BN_dec2bn(BIGNUM **bn, const char *a)
{
    BIGNUM *ret = NULL;
    BN_ULONG l = 0;
    int neg = 0, i, j;
    int num;

    if (a == NULL || *a == '\0')
        return 0;
    if (*a == '-') {
        neg = 1;
        a++;
    }

    for (i = 0; i <= INT_MAX / 4 && ossl_isdigit(a[i]); i++)
        continue;

    if (i == 0 || i > INT_MAX / 4)
        goto err;

    num = i + neg;
    if (bn == NULL)
        return num;

    /*
     * a is the start of the digits, and it is 'i' long. We chop it into
     * BN_DEC_NUM digits at a time
     */
    if (*bn == NULL) {
        if ((ret = BN_new()) == NULL)
            return 0;
    } else {
        ret = *bn;
        BN_zero(ret);
    }

    /* i is the number of digits, a bit of an over expand */
    if (bn_expand(ret, i * 4) == NULL)
        goto err;

    j = BN_DEC_NUM - i % BN_DEC_NUM;
    if (j == BN_DEC_NUM)
        j = 0;
    l = 0;
    while (--i >= 0) {
        l *= 10;
        l += *a - '0';
        a++;
        if (++j == BN_DEC_NUM) {
            if (!BN_mul_word(ret, BN_DEC_CONV)
                || !BN_add_word(ret, l))
                goto err;
            l = 0;
            j = 0;
        }
    }

    bn_correct_top(ret);
    *bn = ret;
    bn_check_top(ret);
    /* Don't set the negative flag if it's zero. */
    if (ret->top != 0)
        ret->neg = neg;
    return num;
 err:
    if (*bn == NULL)
        BN_free(ret);
    return 0;
}