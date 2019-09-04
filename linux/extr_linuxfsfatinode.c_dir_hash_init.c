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
struct msdos_sb_info {int /*<<< orphan*/ * dir_hashtable; int /*<<< orphan*/  dir_hash_lock; } ;

/* Variables and functions */
 int FAT_HASH_SIZE ; 
 int /*<<< orphan*/  INIT_HLIST_HEAD (int /*<<< orphan*/ *) ; 
 struct msdos_sb_info* MSDOS_SB (struct super_block*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dir_hash_init(struct super_block *sb)
{
	struct msdos_sb_info *sbi = MSDOS_SB(sb);
	int i;

	spin_lock_init(&sbi->dir_hash_lock);
	for (i = 0; i < FAT_HASH_SIZE; i++)
		INIT_HLIST_HEAD(&sbi->dir_hashtable[i]);
}