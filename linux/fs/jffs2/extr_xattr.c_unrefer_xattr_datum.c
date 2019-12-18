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
struct jffs2_xattr_datum {int flags; void* node; int /*<<< orphan*/  version; int /*<<< orphan*/  xid; int /*<<< orphan*/  xindex; int /*<<< orphan*/  refcnt; } ;
struct jffs2_sb_info {int /*<<< orphan*/  erase_completion_lock; int /*<<< orphan*/  xattr_dead_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int JFFS2_XFLAGS_DEAD ; 
 int JFFS2_XFLAGS_INVALID ; 
 scalar_t__ atomic_dec_and_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbg_xattr (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jffs2_free_xattr_datum (struct jffs2_xattr_datum*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unload_xattr_datum (struct jffs2_sb_info*,struct jffs2_xattr_datum*) ; 

__attribute__((used)) static void unrefer_xattr_datum(struct jffs2_sb_info *c, struct jffs2_xattr_datum *xd)
{
	/* must be called under down_write(xattr_sem) */
	if (atomic_dec_and_lock(&xd->refcnt, &c->erase_completion_lock)) {
		unload_xattr_datum(c, xd);
		xd->flags |= JFFS2_XFLAGS_DEAD;
		if (xd->node == (void *)xd) {
			BUG_ON(!(xd->flags & JFFS2_XFLAGS_INVALID));
			jffs2_free_xattr_datum(xd);
		} else {
			list_add(&xd->xindex, &c->xattr_dead_list);
		}
		spin_unlock(&c->erase_completion_lock);

		dbg_xattr("xdatum(xid=%u, version=%u) was removed.\n",
			  xd->xid, xd->version);
	}
}