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
struct jffs2_xattr_datum {void* node; int /*<<< orphan*/  xindex; int /*<<< orphan*/  refcnt; } ;
struct jffs2_sb_info {int dummy; } ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jffs2_free_xattr_datum (struct jffs2_xattr_datum*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

void jffs2_release_xattr_datum(struct jffs2_sb_info *c, struct jffs2_xattr_datum *xd)
{
	/* must be called under spin_lock(&c->erase_completion_lock) */
	if (atomic_read(&xd->refcnt) || xd->node != (void *)xd)
		return;

	list_del(&xd->xindex);
	jffs2_free_xattr_datum(xd);
}