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
typedef  scalar_t__ uint32_t ;
struct jffs2_sb_info {struct jffs2_inodirty* wbuf_inodes; } ;
struct jffs2_inodirty {scalar_t__ ino; struct jffs2_inodirty* next; } ;

/* Variables and functions */
 struct jffs2_inodirty inodirty_nomem ; 

__attribute__((used)) static int jffs2_wbuf_pending_for_ino(struct jffs2_sb_info *c, uint32_t ino)
{
	struct jffs2_inodirty *this = c->wbuf_inodes;

	/* If a malloc failed, consider _everything_ dirty */
	if (this == &inodirty_nomem)
		return 1;

	/* If ino == 0, _any_ non-GC writes mean 'yes' */
	if (this && !ino)
		return 1;

	/* Look to see if the inode in question is pending in the wbuf */
	while (this) {
		if (this->ino == ino)
			return 1;
		this = this->next;
	}
	return 0;
}