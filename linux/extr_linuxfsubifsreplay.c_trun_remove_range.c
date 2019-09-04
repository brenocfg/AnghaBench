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
typedef  union ubifs_key {int dummy; } ubifs_key ;
struct ubifs_info {int dummy; } ;
struct replay_entry {int new_size; int old_size; int /*<<< orphan*/  key; } ;
typedef  int /*<<< orphan*/  ino_t ;

/* Variables and functions */
 int UBIFS_BLOCK_SIZE ; 
 int /*<<< orphan*/  data_key_init (struct ubifs_info*,union ubifs_key*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  key_inum (struct ubifs_info*,int /*<<< orphan*/ *) ; 
 int ubifs_tnc_remove_range (struct ubifs_info*,union ubifs_key*,union ubifs_key*) ; 

__attribute__((used)) static int trun_remove_range(struct ubifs_info *c, struct replay_entry *r)
{
	unsigned min_blk, max_blk;
	union ubifs_key min_key, max_key;
	ino_t ino;

	min_blk = r->new_size / UBIFS_BLOCK_SIZE;
	if (r->new_size & (UBIFS_BLOCK_SIZE - 1))
		min_blk += 1;

	max_blk = r->old_size / UBIFS_BLOCK_SIZE;
	if ((r->old_size & (UBIFS_BLOCK_SIZE - 1)) == 0)
		max_blk -= 1;

	ino = key_inum(c, &r->key);

	data_key_init(c, &min_key, ino, min_blk);
	data_key_init(c, &max_key, ino, max_blk);

	return ubifs_tnc_remove_range(c, &min_key, &max_key);
}