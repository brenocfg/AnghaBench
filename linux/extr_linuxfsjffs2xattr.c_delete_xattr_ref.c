#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct jffs2_xattr_ref {int /*<<< orphan*/  xseqno; int /*<<< orphan*/  xid; int /*<<< orphan*/  ino; struct jffs2_xattr_ref* next; struct jffs2_xattr_datum* xd; TYPE_1__* ic; } ;
struct jffs2_xattr_datum {int /*<<< orphan*/  xid; } ;
struct jffs2_sb_info {int /*<<< orphan*/  erase_completion_lock; struct jffs2_xattr_ref* xref_dead_list; } ;
struct TYPE_2__ {int /*<<< orphan*/  ino; } ;

/* Variables and functions */
 int /*<<< orphan*/  XREF_DELETE_MARKER ; 
 int /*<<< orphan*/  dbg_xattr (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unrefer_xattr_datum (struct jffs2_sb_info*,struct jffs2_xattr_datum*) ; 

__attribute__((used)) static void delete_xattr_ref(struct jffs2_sb_info *c, struct jffs2_xattr_ref *ref)
{
	/* must be called under down_write(xattr_sem) */
	struct jffs2_xattr_datum *xd;

	xd = ref->xd;
	ref->xseqno |= XREF_DELETE_MARKER;
	ref->ino = ref->ic->ino;
	ref->xid = ref->xd->xid;
	spin_lock(&c->erase_completion_lock);
	ref->next = c->xref_dead_list;
	c->xref_dead_list = ref;
	spin_unlock(&c->erase_completion_lock);

	dbg_xattr("xref(ino=%u, xid=%u, xseqno=%u) was removed.\n",
		  ref->ino, ref->xid, ref->xseqno);

	unrefer_xattr_datum(c, xd);
}