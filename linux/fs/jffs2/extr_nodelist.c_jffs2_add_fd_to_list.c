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
struct jffs2_sb_info {int dummy; } ;
struct jffs2_full_dirent {scalar_t__ nhash; scalar_t__ version; struct jffs2_full_dirent* next; scalar_t__ raw; int /*<<< orphan*/  ino; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  dbg_dentlist (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jffs2_free_full_dirent (struct jffs2_full_dirent*) ; 
 int /*<<< orphan*/  jffs2_mark_node_obsolete (struct jffs2_sb_info*,scalar_t__) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void jffs2_add_fd_to_list(struct jffs2_sb_info *c, struct jffs2_full_dirent *new, struct jffs2_full_dirent **list)
{
	struct jffs2_full_dirent **prev = list;

	dbg_dentlist("add dirent \"%s\", ino #%u\n", new->name, new->ino);

	while ((*prev) && (*prev)->nhash <= new->nhash) {
		if ((*prev)->nhash == new->nhash && !strcmp((*prev)->name, new->name)) {
			/* Duplicate. Free one */
			if (new->version < (*prev)->version) {
				dbg_dentlist("Eep! Marking new dirent node obsolete, old is \"%s\", ino #%u\n",
					(*prev)->name, (*prev)->ino);
				jffs2_mark_node_obsolete(c, new->raw);
				jffs2_free_full_dirent(new);
			} else {
				dbg_dentlist("marking old dirent \"%s\", ino #%u obsolete\n",
					(*prev)->name, (*prev)->ino);
				new->next = (*prev)->next;
				/* It may have been a 'placeholder' deletion dirent, 
				   if jffs2_can_mark_obsolete() (see jffs2_do_unlink()) */
				if ((*prev)->raw)
					jffs2_mark_node_obsolete(c, ((*prev)->raw));
				jffs2_free_full_dirent(*prev);
				*prev = new;
			}
			return;
		}
		prev = &((*prev)->next);
	}
	new->next = *prev;
	*prev = new;
}