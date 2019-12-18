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
struct jffs2_sb_info {struct jffs2_inodirty* wbuf_inodes; } ;
struct jffs2_inodirty {struct jffs2_inodirty* next; } ;

/* Variables and functions */
 struct jffs2_inodirty inodirty_nomem ; 
 int /*<<< orphan*/  kfree (struct jffs2_inodirty*) ; 

__attribute__((used)) static void jffs2_clear_wbuf_ino_list(struct jffs2_sb_info *c)
{
	struct jffs2_inodirty *this;

	this = c->wbuf_inodes;

	if (this != &inodirty_nomem) {
		while (this) {
			struct jffs2_inodirty *next = this->next;
			kfree(this);
			this = next;
		}
	}
	c->wbuf_inodes = NULL;
}