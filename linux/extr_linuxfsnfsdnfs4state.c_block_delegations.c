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
typedef  int u32 ;
struct knfsd_fh {int /*<<< orphan*/  fh_size; int /*<<< orphan*/  fh_base; } ;
struct bloom_pair {size_t new; scalar_t__ entries; int /*<<< orphan*/  swap_time; int /*<<< orphan*/ * set; } ;

/* Variables and functions */
 int /*<<< orphan*/  __set_bit (int,int /*<<< orphan*/ ) ; 
 struct bloom_pair blocked_delegations ; 
 int /*<<< orphan*/  blocked_delegations_lock ; 
 int jhash (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seconds_since_boot () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void block_delegations(struct knfsd_fh *fh)
{
	u32 hash;
	struct bloom_pair *bd = &blocked_delegations;

	hash = jhash(&fh->fh_base, fh->fh_size, 0);

	spin_lock(&blocked_delegations_lock);
	__set_bit(hash&255, bd->set[bd->new]);
	__set_bit((hash>>8)&255, bd->set[bd->new]);
	__set_bit((hash>>16)&255, bd->set[bd->new]);
	if (bd->entries == 0)
		bd->swap_time = seconds_since_boot();
	bd->entries += 1;
	spin_unlock(&blocked_delegations_lock);
}