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
struct jffs2_xattr_ref {scalar_t__ xseqno; struct jffs2_xattr_ref* next; TYPE_1__* xd; } ;
struct jffs2_sb_info {int /*<<< orphan*/  xattr_sem; } ;
struct jffs2_inode_cache {int flags; struct jffs2_xattr_ref* xref; } ;
struct TYPE_2__ {scalar_t__ xprefix; int /*<<< orphan*/  xname; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int INO_FLAGS_XATTR_CHECKED ; 
 int /*<<< orphan*/  JFFS2_XFLAGS_BIND ; 
 int /*<<< orphan*/  delete_xattr_ref (struct jffs2_sb_info*,struct jffs2_xattr_ref*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 scalar_t__ likely (int) ; 
 int load_xattr_datum (struct jffs2_sb_info*,TYPE_1__*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int check_xattr_ref_inode(struct jffs2_sb_info *c, struct jffs2_inode_cache *ic)
{
	/* success of check_xattr_ref_inode() means that inode (ic) dose not have
	 * duplicate name/value pairs. If duplicate name/value pair would be found,
	 * one will be removed.
	 */
	struct jffs2_xattr_ref *ref, *cmp, **pref, **pcmp;
	int rc = 0;

	if (likely(ic->flags & INO_FLAGS_XATTR_CHECKED))
		return 0;
	down_write(&c->xattr_sem);
 retry:
	rc = 0;
	for (ref=ic->xref, pref=&ic->xref; ref; pref=&ref->next, ref=ref->next) {
		if (!ref->xd->xname) {
			rc = load_xattr_datum(c, ref->xd);
			if (unlikely(rc > 0)) {
				*pref = ref->next;
				delete_xattr_ref(c, ref);
				goto retry;
			} else if (unlikely(rc < 0))
				goto out;
		}
		for (cmp=ref->next, pcmp=&ref->next; cmp; pcmp=&cmp->next, cmp=cmp->next) {
			if (!cmp->xd->xname) {
				ref->xd->flags |= JFFS2_XFLAGS_BIND;
				rc = load_xattr_datum(c, cmp->xd);
				ref->xd->flags &= ~JFFS2_XFLAGS_BIND;
				if (unlikely(rc > 0)) {
					*pcmp = cmp->next;
					delete_xattr_ref(c, cmp);
					goto retry;
				} else if (unlikely(rc < 0))
					goto out;
			}
			if (ref->xd->xprefix == cmp->xd->xprefix
			    && !strcmp(ref->xd->xname, cmp->xd->xname)) {
				if (ref->xseqno > cmp->xseqno) {
					*pcmp = cmp->next;
					delete_xattr_ref(c, cmp);
				} else {
					*pref = ref->next;
					delete_xattr_ref(c, ref);
				}
				goto retry;
			}
		}
	}
	ic->flags |= INO_FLAGS_XATTR_CHECKED;
 out:
	up_write(&c->xattr_sem);

	return rc;
}