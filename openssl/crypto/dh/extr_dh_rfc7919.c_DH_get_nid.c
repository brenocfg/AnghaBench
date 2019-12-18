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
struct TYPE_3__ {int /*<<< orphan*/ * q; int /*<<< orphan*/ * p; int /*<<< orphan*/  g; } ;
typedef  TYPE_1__ DH ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_dup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 int BN_get_word (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_rshift1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int NID_ffdhe2048 ; 
 int NID_ffdhe3072 ; 
 int NID_ffdhe4096 ; 
 int NID_ffdhe6144 ; 
 int NID_ffdhe8192 ; 
 int NID_undef ; 
 int /*<<< orphan*/  _bignum_ffdhe2048_p ; 
 int /*<<< orphan*/  _bignum_ffdhe3072_p ; 
 int /*<<< orphan*/  _bignum_ffdhe4096_p ; 
 int /*<<< orphan*/  _bignum_ffdhe6144_p ; 
 int /*<<< orphan*/  _bignum_ffdhe8192_p ; 

int DH_get_nid(const DH *dh)
{
    int nid;

    if (BN_get_word(dh->g) != 2)
        return NID_undef;
    if (!BN_cmp(dh->p, &_bignum_ffdhe2048_p))
        nid = NID_ffdhe2048;
    else if (!BN_cmp(dh->p, &_bignum_ffdhe3072_p))
        nid = NID_ffdhe3072;
    else if (!BN_cmp(dh->p, &_bignum_ffdhe4096_p))
        nid = NID_ffdhe4096;
    else if (!BN_cmp(dh->p, &_bignum_ffdhe6144_p))
        nid = NID_ffdhe6144;
    else if (!BN_cmp(dh->p, &_bignum_ffdhe8192_p))
        nid = NID_ffdhe8192;
    else
        return NID_undef;
    if (dh->q != NULL) {
        BIGNUM *q = BN_dup(dh->p);

        /* Check q = p * 2 + 1 we already know q is odd, so just shift right */
        if (q == NULL || !BN_rshift1(q, q) || !BN_cmp(dh->q, q))
            nid = NID_undef;
        BN_free(q);
    }
    return nid;
}