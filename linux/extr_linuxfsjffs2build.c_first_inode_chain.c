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
struct jffs2_sb_info {int inocache_hashsize; struct jffs2_inode_cache** inocache_list; } ;
struct jffs2_inode_cache {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline struct jffs2_inode_cache *
first_inode_chain(int *i, struct jffs2_sb_info *c)
{
	for (; *i < c->inocache_hashsize; (*i)++) {
		if (c->inocache_list[*i])
			return c->inocache_list[*i];
	}
	return NULL;
}