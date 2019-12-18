#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct jffs2_xattr_ref {int ino; int xid; int xseqno; TYPE_2__* xd; TYPE_1__* ic; } ;
struct jffs2_unknown_node {int dummy; } ;
struct jffs2_sb_info {int highest_xseqno; } ;
struct jffs2_raw_xref {void* node_crc; void* xseqno; void* xid; void* ino; void* hdr_crc; void* totlen; void* nodetype; void* magic; } ;
typedef  int /*<<< orphan*/  rr ;
struct TYPE_4__ {int xid; } ;
struct TYPE_3__ {int ino; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  JFFS2_MAGIC_BITMASK ; 
 int /*<<< orphan*/  JFFS2_NODETYPE_XREF ; 
 int /*<<< orphan*/  JFFS2_WARNING (char*,int,int,size_t,int) ; 
 int PAD (int) ; 
 int REF_OBSOLETE ; 
 int REF_PRISTINE ; 
 int XREF_DELETE_MARKER ; 
 void* cpu_to_je16 (int /*<<< orphan*/ ) ; 
 void* cpu_to_je32 (int) ; 
 int crc32 (int /*<<< orphan*/ ,struct jffs2_raw_xref*,int) ; 
 int /*<<< orphan*/  dbg_xattr (char*,int,int) ; 
 scalar_t__ is_xattr_ref_dead (struct jffs2_xattr_ref*) ; 
 int /*<<< orphan*/  jffs2_add_physical_node_ref (struct jffs2_sb_info*,int,int,void*) ; 
 int jffs2_flash_write (struct jffs2_sb_info*,int,int,size_t*,char*) ; 
 int write_ofs (struct jffs2_sb_info*) ; 

__attribute__((used)) static int save_xattr_ref(struct jffs2_sb_info *c, struct jffs2_xattr_ref *ref)
{
	/* must be called under down_write(xattr_sem) */
	struct jffs2_raw_xref rr;
	size_t length;
	uint32_t xseqno, phys_ofs = write_ofs(c);
	int ret;

	rr.magic = cpu_to_je16(JFFS2_MAGIC_BITMASK);
	rr.nodetype = cpu_to_je16(JFFS2_NODETYPE_XREF);
	rr.totlen = cpu_to_je32(PAD(sizeof(rr)));
	rr.hdr_crc = cpu_to_je32(crc32(0, &rr, sizeof(struct jffs2_unknown_node) - 4));

	xseqno = (c->highest_xseqno += 2);
	if (is_xattr_ref_dead(ref)) {
		xseqno |= XREF_DELETE_MARKER;
		rr.ino = cpu_to_je32(ref->ino);
		rr.xid = cpu_to_je32(ref->xid);
	} else {
		rr.ino = cpu_to_je32(ref->ic->ino);
		rr.xid = cpu_to_je32(ref->xd->xid);
	}
	rr.xseqno = cpu_to_je32(xseqno);
	rr.node_crc = cpu_to_je32(crc32(0, &rr, sizeof(rr) - 4));

	ret = jffs2_flash_write(c, phys_ofs, sizeof(rr), &length, (char *)&rr);
	if (ret || sizeof(rr) != length) {
		JFFS2_WARNING("jffs2_flash_write() returned %d, request=%zu, retlen=%zu, at %#08x\n",
			      ret, sizeof(rr), length, phys_ofs);
		ret = ret ? ret : -EIO;
		if (length)
			jffs2_add_physical_node_ref(c, phys_ofs | REF_OBSOLETE, PAD(sizeof(rr)), NULL);

		return ret;
	}
	/* success */
	ref->xseqno = xseqno;
	jffs2_add_physical_node_ref(c, phys_ofs | REF_PRISTINE, PAD(sizeof(rr)), (void *)ref);

	dbg_xattr("success on saving xref (ino=%u, xid=%u)\n", ref->ic->ino, ref->xd->xid);

	return 0;
}