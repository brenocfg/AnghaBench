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
struct the_nilfs {unsigned int ns_sb_update_freq; int /*<<< orphan*/  ns_sem; } ;
struct nilfs_superblock_attr {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t
nilfs_superblock_sb_update_frequency_show(struct nilfs_superblock_attr *attr,
					    struct the_nilfs *nilfs,
					    char *buf)
{
	unsigned int sb_update_freq;

	down_read(&nilfs->ns_sem);
	sb_update_freq = nilfs->ns_sb_update_freq;
	up_read(&nilfs->ns_sem);

	return snprintf(buf, PAGE_SIZE, "%u\n", sb_update_freq);
}