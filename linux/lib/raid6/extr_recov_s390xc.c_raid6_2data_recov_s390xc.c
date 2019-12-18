#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct TYPE_2__ {int /*<<< orphan*/  (* gen_syndrome ) (int,size_t,void**) ;} ;

/* Variables and functions */
 TYPE_1__ raid6_call ; 
 scalar_t__ raid6_empty_zero_page ; 
 size_t* raid6_gfexi ; 
 size_t* raid6_gfexp ; 
 size_t* raid6_gfinv ; 
 size_t** raid6_gfmul ; 
 int /*<<< orphan*/  stub1 (int,size_t,void**) ; 
 int /*<<< orphan*/  xor_block (size_t*,size_t*) ; 

__attribute__((used)) static void raid6_2data_recov_s390xc(int disks, size_t bytes, int faila,
		int failb, void **ptrs)
{
	u8 *p, *q, *dp, *dq;
	const u8 *pbmul;	/* P multiplier table for B data */
	const u8 *qmul;		/* Q multiplier table (for both) */
	int i;

	p = (u8 *)ptrs[disks-2];
	q = (u8 *)ptrs[disks-1];

	/* Compute syndrome with zero for the missing data pages
	   Use the dead data pages as temporary storage for
	   delta p and delta q */
	dp = (u8 *)ptrs[faila];
	ptrs[faila] = (void *)raid6_empty_zero_page;
	ptrs[disks-2] = dp;
	dq = (u8 *)ptrs[failb];
	ptrs[failb] = (void *)raid6_empty_zero_page;
	ptrs[disks-1] = dq;

	raid6_call.gen_syndrome(disks, bytes, ptrs);

	/* Restore pointer table */
	ptrs[faila]   = dp;
	ptrs[failb]   = dq;
	ptrs[disks-2] = p;
	ptrs[disks-1] = q;

	/* Now, pick the proper data tables */
	pbmul = raid6_gfmul[raid6_gfexi[failb-faila]];
	qmul  = raid6_gfmul[raid6_gfinv[raid6_gfexp[faila]^raid6_gfexp[failb]]];

	/* Now do it... */
	while (bytes) {
		xor_block(dp, p);
		xor_block(dq, q);
		for (i = 0; i < 256; i++)
			dq[i] = pbmul[dp[i]] ^ qmul[dq[i]];
		xor_block(dp, dq);
		p += 256;
		q += 256;
		dp += 256;
		dq += 256;
		bytes -= 256;
	}
}