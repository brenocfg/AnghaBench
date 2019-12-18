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
struct TYPE_3__ {int top; int* d; } ;
typedef  int BN_ULONG ;
typedef  int BN_ULLONG ;
typedef  TYPE_1__ BIGNUM ;

/* Variables and functions */
 scalar_t__ BN_BITS2 ; 
 int BN_BITS4 ; 
 int BN_MASK2 ; 
 int BN_MASK2l ; 

BN_ULONG BN_mod_word(const BIGNUM *a, BN_ULONG w)
	{
#ifndef BN_LLONG
	BN_ULONG ret=0;
#else
	BN_ULLONG ret=0;
#endif
	int i;

	w&=BN_MASK2;
	for (i=a->top-1; i>=0; i--)
		{
#ifndef BN_LLONG
		ret=((ret<<BN_BITS4)|((a->d[i]>>BN_BITS4)&BN_MASK2l))%w;
		ret=((ret<<BN_BITS4)|(a->d[i]&BN_MASK2l))%w;
#else
		ret=(BN_ULLONG)(((ret<<(BN_ULLONG)BN_BITS2)|a->d[i])%
			(BN_ULLONG)w);
#endif
		}
	return((BN_ULONG)ret);
	}