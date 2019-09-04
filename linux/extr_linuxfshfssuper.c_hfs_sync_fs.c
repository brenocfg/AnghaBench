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
struct super_block {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hfs_mdb_commit (struct super_block*) ; 

__attribute__((used)) static int hfs_sync_fs(struct super_block *sb, int wait)
{
	hfs_mdb_commit(sb);
	return 0;
}