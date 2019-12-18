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
typedef  int /*<<< orphan*/  uint32_t ;
struct jffs2_sb_info {struct jffs2_inodirty* wbuf_inodes; } ;
struct jffs2_inodirty {struct jffs2_inodirty* next; int /*<<< orphan*/  ino; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct jffs2_inodirty inodirty_nomem ; 
 int /*<<< orphan*/  jffs2_clear_wbuf_ino_list (struct jffs2_sb_info*) ; 
 int /*<<< orphan*/  jffs2_dbg (int,char*) ; 
 int /*<<< orphan*/  jffs2_dirty_trigger (struct jffs2_sb_info*) ; 
 scalar_t__ jffs2_wbuf_pending_for_ino (struct jffs2_sb_info*,int /*<<< orphan*/ ) ; 
 struct jffs2_inodirty* kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void jffs2_wbuf_dirties_inode(struct jffs2_sb_info *c, uint32_t ino)
{
	struct jffs2_inodirty *new;

	/* Schedule delayed write-buffer write-out */
	jffs2_dirty_trigger(c);

	if (jffs2_wbuf_pending_for_ino(c, ino))
		return;

	new = kmalloc(sizeof(*new), GFP_KERNEL);
	if (!new) {
		jffs2_dbg(1, "No memory to allocate inodirty. Fallback to all considered dirty\n");
		jffs2_clear_wbuf_ino_list(c);
		c->wbuf_inodes = &inodirty_nomem;
		return;
	}
	new->ino = ino;
	new->next = c->wbuf_inodes;
	c->wbuf_inodes = new;
	return;
}