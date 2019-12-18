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
struct ubifs_info {int ro_error; TYPE_1__* vfs_sb; scalar_t__ no_chk_data_crc; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  SB_RDONLY ; 
 int /*<<< orphan*/  dump_stack () ; 
 int /*<<< orphan*/  ubifs_warn (struct ubifs_info*,char*,int) ; 

void ubifs_ro_mode(struct ubifs_info *c, int err)
{
	if (!c->ro_error) {
		c->ro_error = 1;
		c->no_chk_data_crc = 0;
		c->vfs_sb->s_flags |= SB_RDONLY;
		ubifs_warn(c, "switched to read-only mode, error %d", err);
		dump_stack();
	}
}