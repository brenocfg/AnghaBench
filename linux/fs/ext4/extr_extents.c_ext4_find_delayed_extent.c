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
struct inode {int dummy; } ;
struct extent_status {scalar_t__ es_pblk; int es_lblk; int es_len; } ;
typedef  int ext4_lblk_t ;

/* Variables and functions */
 int EXT_MAX_BLOCKS ; 
 int /*<<< orphan*/  ext4_es_find_extent_range (struct inode*,int /*<<< orphan*/ *,int,int,struct extent_status*) ; 
 int /*<<< orphan*/  ext4_es_is_delayed ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int ext4_find_delayed_extent(struct inode *inode,
				    struct extent_status *newes)
{
	struct extent_status es;
	ext4_lblk_t block, next_del;

	if (newes->es_pblk == 0) {
		ext4_es_find_extent_range(inode, &ext4_es_is_delayed,
					  newes->es_lblk,
					  newes->es_lblk + newes->es_len - 1,
					  &es);

		/*
		 * No extent in extent-tree contains block @newes->es_pblk,
		 * then the block may stay in 1)a hole or 2)delayed-extent.
		 */
		if (es.es_len == 0)
			/* A hole found. */
			return 0;

		if (es.es_lblk > newes->es_lblk) {
			/* A hole found. */
			newes->es_len = min(es.es_lblk - newes->es_lblk,
					    newes->es_len);
			return 0;
		}

		newes->es_len = es.es_lblk + es.es_len - newes->es_lblk;
	}

	block = newes->es_lblk + newes->es_len;
	ext4_es_find_extent_range(inode, &ext4_es_is_delayed, block,
				  EXT_MAX_BLOCKS, &es);
	if (es.es_len == 0)
		next_del = EXT_MAX_BLOCKS;
	else
		next_del = es.es_lblk;

	return next_del;
}