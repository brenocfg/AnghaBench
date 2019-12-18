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
struct jffs2_xattr_ref {void* node; struct jffs2_xattr_ref* next; } ;
struct jffs2_sb_info {struct jffs2_xattr_ref* xref_dead_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  jffs2_free_xattr_ref (struct jffs2_xattr_ref*) ; 

void jffs2_release_xattr_ref(struct jffs2_sb_info *c, struct jffs2_xattr_ref *ref)
{
	/* must be called under spin_lock(&c->erase_completion_lock) */
	struct jffs2_xattr_ref *tmp, **ptmp;

	if (ref->node != (void *)ref)
		return;

	for (tmp=c->xref_dead_list, ptmp=&c->xref_dead_list; tmp; ptmp=&tmp->next, tmp=tmp->next) {
		if (ref == tmp) {
			*ptmp = tmp->next;
			break;
		}
	}
	jffs2_free_xattr_ref(ref);
}