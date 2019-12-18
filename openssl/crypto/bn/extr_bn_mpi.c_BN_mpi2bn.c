#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int neg; scalar_t__ top; } ;
typedef  TYPE_1__ BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_F_BN_MPI2BN ; 
 int /*<<< orphan*/  BN_R_ENCODING_ERROR ; 
 int /*<<< orphan*/  BN_R_INVALID_LENGTH ; 
 int /*<<< orphan*/ * BN_bin2bn (unsigned char const*,int,TYPE_1__*) ; 
 int /*<<< orphan*/  BN_clear_bit (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  BN_free (TYPE_1__*) ; 
 TYPE_1__* BN_new () ; 
 scalar_t__ BN_num_bits (TYPE_1__*) ; 
 int /*<<< orphan*/  BNerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bn_check_top (TYPE_1__*) ; 

BIGNUM *BN_mpi2bn(const unsigned char *d, int n, BIGNUM *ain)
{
    long len;
    int neg = 0;
    BIGNUM *a = NULL;

    if (n < 4) {
        BNerr(BN_F_BN_MPI2BN, BN_R_INVALID_LENGTH);
        return NULL;
    }
    len = ((long)d[0] << 24) | ((long)d[1] << 16) | ((int)d[2] << 8) | (int)
        d[3];
    if ((len + 4) != n) {
        BNerr(BN_F_BN_MPI2BN, BN_R_ENCODING_ERROR);
        return NULL;
    }

    if (ain == NULL)
        a = BN_new();
    else
        a = ain;

    if (a == NULL)
        return NULL;

    if (len == 0) {
        a->neg = 0;
        a->top = 0;
        return a;
    }
    d += 4;
    if ((*d) & 0x80)
        neg = 1;
    if (BN_bin2bn(d, (int)len, a) == NULL) {
        if (ain == NULL)
            BN_free(a);
        return NULL;
    }
    a->neg = neg;
    if (neg) {
        BN_clear_bit(a, BN_num_bits(a) - 1);
    }
    bn_check_top(a);
    return a;
}