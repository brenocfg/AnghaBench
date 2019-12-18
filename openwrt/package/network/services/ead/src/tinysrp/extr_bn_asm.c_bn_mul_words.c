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
typedef  int /*<<< orphan*/  BN_ULONG ;

/* Variables and functions */
 int /*<<< orphan*/  HBITS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LBITS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  mul (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

BN_ULONG bn_mul_words(BN_ULONG *rp, BN_ULONG *ap, int num, BN_ULONG w)
	{
	BN_ULONG carry=0;
	BN_ULONG bl,bh;

	assert(num >= 0);
	if (num <= 0) return((BN_ULONG)0);

	bl=LBITS(w);
	bh=HBITS(w);

	for (;;)
		{
		mul(rp[0],ap[0],bl,bh,carry);
		if (--num == 0) break;
		mul(rp[1],ap[1],bl,bh,carry);
		if (--num == 0) break;
		mul(rp[2],ap[2],bl,bh,carry);
		if (--num == 0) break;
		mul(rp[3],ap[3],bl,bh,carry);
		if (--num == 0) break;
		ap+=4;
		rp+=4;
		}
	return(carry);
	}