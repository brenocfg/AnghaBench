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
struct jffs2_xattr_datum {int flags; struct jffs2_raw_node_ref* node; int /*<<< orphan*/  version; int /*<<< orphan*/  xid; scalar_t__ value_len; scalar_t__ name_len; } ;
struct jffs2_sb_info {int /*<<< orphan*/  xattr_sem; } ;
struct jffs2_raw_xattr {int dummy; } ;
struct jffs2_raw_node_ref {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  JFFS2_SUMMARY_XATTR_SIZE ; 
 int /*<<< orphan*/  JFFS2_WARNING (char*,int,int /*<<< orphan*/ ) ; 
 int JFFS2_XFLAGS_DEAD ; 
 int JFFS2_XFLAGS_INVALID ; 
 int /*<<< orphan*/  PAD (scalar_t__) ; 
 int /*<<< orphan*/  dbg_xattr (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jffs2_mark_node_obsolete (struct jffs2_sb_info*,struct jffs2_raw_node_ref*) ; 
 int jffs2_reserve_space_gc (struct jffs2_sb_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int load_xattr_datum (struct jffs2_sb_info*,struct jffs2_xattr_datum*) ; 
 int /*<<< orphan*/  ref_offset (struct jffs2_raw_node_ref*) ; 
 int save_xattr_datum (struct jffs2_sb_info*,struct jffs2_xattr_datum*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int jffs2_garbage_collect_xattr_datum(struct jffs2_sb_info *c, struct jffs2_xattr_datum *xd,
				      struct jffs2_raw_node_ref *raw)
{
	uint32_t totlen, length, old_ofs;
	int rc = 0;

	down_write(&c->xattr_sem);
	if (xd->node != raw)
		goto out;
	if (xd->flags & (JFFS2_XFLAGS_DEAD|JFFS2_XFLAGS_INVALID))
		goto out;

	rc = load_xattr_datum(c, xd);
	if (unlikely(rc)) {
		rc = (rc > 0) ? 0 : rc;
		goto out;
	}
	old_ofs = ref_offset(xd->node);
	totlen = PAD(sizeof(struct jffs2_raw_xattr)
			+ xd->name_len + 1 + xd->value_len);
	rc = jffs2_reserve_space_gc(c, totlen, &length, JFFS2_SUMMARY_XATTR_SIZE);
	if (rc) {
		JFFS2_WARNING("jffs2_reserve_space_gc()=%d, request=%u\n", rc, totlen);
		goto out;
	}
	rc = save_xattr_datum(c, xd);
	if (!rc)
		dbg_xattr("xdatum (xid=%u, version=%u) GC'ed from %#08x to %08x\n",
			  xd->xid, xd->version, old_ofs, ref_offset(xd->node));
 out:
	if (!rc)
		jffs2_mark_node_obsolete(c, raw);
	up_write(&c->xattr_sem);
	return rc;
}