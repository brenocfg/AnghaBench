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
struct the_nilfs {unsigned int ns_sb_update_freq; int /*<<< orphan*/  ns_sem; int /*<<< orphan*/  ns_sb; } ;
struct nilfs_superblock_attr {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 unsigned int NILFS_SB_FREQ ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int kstrtouint (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  nilfs_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  skip_spaces (char const*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t
nilfs_superblock_sb_update_frequency_store(struct nilfs_superblock_attr *attr,
					    struct the_nilfs *nilfs,
					    const char *buf, size_t count)
{
	unsigned int val;
	int err;

	err = kstrtouint(skip_spaces(buf), 0, &val);
	if (err) {
		nilfs_msg(nilfs->ns_sb, KERN_ERR,
			  "unable to convert string: err=%d", err);
		return err;
	}

	if (val < NILFS_SB_FREQ) {
		val = NILFS_SB_FREQ;
		nilfs_msg(nilfs->ns_sb, KERN_WARNING,
			  "superblock update frequency cannot be lesser than 10 seconds");
	}

	down_write(&nilfs->ns_sem);
	nilfs->ns_sb_update_freq = val;
	up_write(&nilfs->ns_sem);

	return count;
}