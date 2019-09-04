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
struct super_block {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  mdb_work; } ;

/* Variables and functions */
 TYPE_1__* HFS_SB (struct super_block*) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hfs_mdb_close (struct super_block*) ; 
 int /*<<< orphan*/  hfs_mdb_put (struct super_block*) ; 

__attribute__((used)) static void hfs_put_super(struct super_block *sb)
{
	cancel_delayed_work_sync(&HFS_SB(sb)->mdb_work);
	hfs_mdb_close(sb);
	/* release the MDB's resources */
	hfs_mdb_put(sb);
}