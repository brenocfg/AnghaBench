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
 int /*<<< orphan*/  GOSSIP_SUPER_DEBUG ; 
 int /*<<< orphan*/  gossip_debug (int /*<<< orphan*/ ,char*) ; 
 int parse_mount_options (struct super_block*,char*,int) ; 

__attribute__((used)) static int orangefs_remount_fs(struct super_block *sb, int *flags, char *data)
{
	gossip_debug(GOSSIP_SUPER_DEBUG, "orangefs_remount_fs: called\n");
	return parse_mount_options(sb, data, 1);
}