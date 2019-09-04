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
typedef  int uint32_t ;
struct jffs2_sb_info {int dummy; } ;
struct jffs2_raw_inode {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline int min_free(struct jffs2_sb_info *c)
{
	uint32_t min = 2 * sizeof(struct jffs2_raw_inode);
#ifdef CONFIG_JFFS2_FS_WRITEBUFFER
	if (!jffs2_can_mark_obsolete(c) && min < c->wbuf_pagesize)
		return c->wbuf_pagesize;
#endif
	return min;

}