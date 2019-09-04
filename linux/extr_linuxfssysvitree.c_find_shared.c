#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_6__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ sysv_zone_t ;
struct inode {int dummy; } ;
struct TYPE_8__ {scalar_t__ b_data; } ;
struct TYPE_7__ {TYPE_6__* bh; scalar_t__* p; int /*<<< orphan*/  key; } ;
typedef  TYPE_1__ Indirect ;

/* Variables and functions */
 scalar_t__ all_zeroes (scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  brelse (TYPE_6__*) ; 
 TYPE_1__* get_branch (struct inode*,int,int*,TYPE_1__*,int*) ; 
 int /*<<< orphan*/  pointers_lock ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static Indirect *find_shared(struct inode *inode,
				int depth,
				int offsets[],
				Indirect chain[],
				sysv_zone_t *top)
{
	Indirect *partial, *p;
	int k, err;

	*top = 0;
	for (k = depth; k > 1 && !offsets[k-1]; k--)
		;

	write_lock(&pointers_lock);
	partial = get_branch(inode, k, offsets, chain, &err);
	if (!partial)
		partial = chain + k-1;
	/*
	 * If the branch acquired continuation since we've looked at it -
	 * fine, it should all survive and (new) top doesn't belong to us.
	 */
	if (!partial->key && *partial->p) {
		write_unlock(&pointers_lock);
		goto no_top;
	}
	for (p=partial; p>chain && all_zeroes((sysv_zone_t*)p->bh->b_data,p->p); p--)
		;
	/*
	 * OK, we've found the last block that must survive. The rest of our
	 * branch should be detached before unlocking. However, if that rest
	 * of branch is all ours and does not grow immediately from the inode
	 * it's easier to cheat and just decrement partial->p.
	 */
	if (p == chain + k - 1 && p > chain) {
		p->p--;
	} else {
		*top = *p->p;
		*p->p = 0;
	}
	write_unlock(&pointers_lock);

	while (partial > p) {
		brelse(partial->bh);
		partial--;
	}
no_top:
	return partial;
}