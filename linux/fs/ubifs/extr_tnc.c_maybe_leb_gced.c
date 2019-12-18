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
struct ubifs_info {int gced_lnum; int gc_seq; } ;

/* Variables and functions */
 int /*<<< orphan*/  smp_rmb () ; 

__attribute__((used)) static int maybe_leb_gced(struct ubifs_info *c, int lnum, int gc_seq1)
{
	int gc_seq2, gced_lnum;

	gced_lnum = c->gced_lnum;
	smp_rmb();
	gc_seq2 = c->gc_seq;
	/* Same seq means no GC */
	if (gc_seq1 == gc_seq2)
		return 0;
	/* Different by more than 1 means we don't know */
	if (gc_seq1 + 1 != gc_seq2)
		return 1;
	/*
	 * We have seen the sequence number has increased by 1. Now we need to
	 * be sure we read the right LEB number, so read it again.
	 */
	smp_rmb();
	if (gced_lnum != c->gced_lnum)
		return 1;
	/* Finally we can check lnum */
	if (gced_lnum == lnum)
		return 1;
	return 0;
}