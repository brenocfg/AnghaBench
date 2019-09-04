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
 int layout_in_empty_space (struct ubifs_info*) ; 
 int layout_in_gaps (struct ubifs_info*,int) ; 

__attribute__((used)) static int layout_commit(struct ubifs_info *c, int no_space, int cnt)
{
	int err;

	if (no_space) {
		err = layout_in_gaps(c, cnt);
		if (err)
			return err;
	}
	err = layout_in_empty_space(c);
	return err;
}