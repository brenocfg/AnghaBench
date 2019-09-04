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
struct ubifs_info {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  add_size ; 
 int /*<<< orphan*/  dbg_is_chk_index (struct ubifs_info*) ; 
 int dbg_walk_index (struct ubifs_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,long long*) ; 
 int /*<<< orphan*/  dump_stack () ; 
 int /*<<< orphan*/  ubifs_err (struct ubifs_info*,char*,long long,...) ; 

int dbg_check_idx_size(struct ubifs_info *c, long long idx_size)
{
	int err;
	long long calc = 0;

	if (!dbg_is_chk_index(c))
		return 0;

	err = dbg_walk_index(c, NULL, add_size, &calc);
	if (err) {
		ubifs_err(c, "error %d while walking the index", err);
		return err;
	}

	if (calc != idx_size) {
		ubifs_err(c, "index size check failed: calculated size is %lld, should be %lld",
			  calc, idx_size);
		dump_stack();
		return -EINVAL;
	}

	return 0;
}