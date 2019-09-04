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
struct grub_afs_sblock {int block_per_group; } ;
struct grub_afs_blockrun {int /*<<< orphan*/  start; int /*<<< orphan*/  group; } ;
typedef  int grub_afs_off_t ;

/* Variables and functions */
 int grub_afs_to_cpu16 (int /*<<< orphan*/ ) ; 
 scalar_t__ grub_afs_to_cpu32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static grub_afs_off_t
grub_afs_run_to_num (struct grub_afs_sblock *sb,
                     struct grub_afs_blockrun *run)
{
  return ((grub_afs_off_t) grub_afs_to_cpu32 (run->group)
	  * sb->block_per_group + grub_afs_to_cpu16 (run->start));
}