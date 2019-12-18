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
struct bloom_pair {scalar_t__ entries; int swap_time; scalar_t__ old_entries; size_t new; int /*<<< orphan*/ * set; } ;

/* Variables and functions */
 struct bloom_pair blocked_delegations ; 
 int /*<<< orphan*/  blocked_delegations_lock ; 
 int jhash (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int seconds_since_boot () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int delegation_blocked(struct knfsd_fh *fh)
{
	u32 hash;
	struct bloom_pair *bd = &blocked_delegations;

	if (bd->entries == 0)
		return 0;
	if (seconds_since_boot() - bd->swap_time > 30) {
		spin_lock(&blocked_delegations_lock);
		if (seconds_since_boot() - bd->swap_time > 30) {
			bd->entries -= bd->old_entries;
			bd->old_entries = bd->entries;
			memset(bd->set[bd->new], 0,
			       sizeof(bd->set[0]));
			bd->new = 1-bd->new;
			bd->swap_time = seconds_since_boot();
		}
		spin_unlock(&blocked_delegations_lock);
	}
	hash = jhash(&fh->fh_base, fh->fh_size, 0);
	if (test_bit(hash&255, bd->set[0]) &&
	    test_bit((hash>>8)&255, bd->set[0]) &&
	    test_bit((hash>>16)&255, bd->set[0]))
		return 1;

	if (test_bit(hash&255, bd->set[1]) &&
	    test_bit((hash>>8)&255, bd->set[1]) &&
	    test_bit((hash>>16)&255, bd->set[1]))
		return 1;

	return 0;
}