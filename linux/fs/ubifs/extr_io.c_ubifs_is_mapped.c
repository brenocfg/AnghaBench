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
struct ubifs_info {int /*<<< orphan*/  ubi; } ;

/* Variables and functions */
 int /*<<< orphan*/  dump_stack () ; 
 int ubi_is_mapped (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ubifs_err (struct ubifs_info const*,char*,int,int) ; 

int ubifs_is_mapped(const struct ubifs_info *c, int lnum)
{
	int err;

	err = ubi_is_mapped(c->ubi, lnum);
	if (err < 0) {
		ubifs_err(c, "ubi_is_mapped failed for LEB %d, error %d",
			  lnum, err);
		dump_stack();
	}
	return err;
}