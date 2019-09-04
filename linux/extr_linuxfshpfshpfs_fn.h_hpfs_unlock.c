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
struct hpfs_sb_info {int /*<<< orphan*/  hpfs_mutex; } ;

/* Variables and functions */
 struct hpfs_sb_info* hpfs_sb (struct super_block*) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void hpfs_unlock(struct super_block *s)
{
	struct hpfs_sb_info *sbi = hpfs_sb(s);
	mutex_unlock(&sbi->hpfs_mutex);
}