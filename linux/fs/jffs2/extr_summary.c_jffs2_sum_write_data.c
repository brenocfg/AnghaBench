#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {union jffs2_sum_mem* next; int /*<<< orphan*/  nodetype; } ;
struct TYPE_9__ {int /*<<< orphan*/  offset; int /*<<< orphan*/  nodetype; } ;
struct TYPE_8__ {int /*<<< orphan*/  totlen; int /*<<< orphan*/  offset; int /*<<< orphan*/  version; int /*<<< orphan*/  xid; int /*<<< orphan*/  nodetype; } ;
struct TYPE_12__ {int /*<<< orphan*/  nsize; int /*<<< orphan*/  name; int /*<<< orphan*/  type; int /*<<< orphan*/  ino; int /*<<< orphan*/  version; int /*<<< orphan*/  pino; int /*<<< orphan*/  offset; int /*<<< orphan*/  totlen; int /*<<< orphan*/  nodetype; } ;
struct TYPE_11__ {int /*<<< orphan*/  totlen; int /*<<< orphan*/  offset; int /*<<< orphan*/  version; int /*<<< orphan*/  inode; int /*<<< orphan*/  nodetype; } ;
union jffs2_sum_mem {TYPE_3__ u; TYPE_2__ r; TYPE_1__ x; TYPE_5__ d; TYPE_4__ i; } ;
typedef  int uint32_t ;
struct kvec {int iov_len; struct jffs2_raw_summary* iov_base; } ;
struct jffs2_unknown_node {int dummy; } ;
struct jffs2_sum_xref_flash {int /*<<< orphan*/  offset; int /*<<< orphan*/  nodetype; } ;
struct jffs2_sum_xattr_flash {int /*<<< orphan*/  totlen; int /*<<< orphan*/  offset; int /*<<< orphan*/  version; int /*<<< orphan*/  xid; int /*<<< orphan*/  nodetype; } ;
struct jffs2_sum_marker {void* magic; void* offset; } ;
struct jffs2_sum_inode_flash {int /*<<< orphan*/  totlen; int /*<<< orphan*/  offset; int /*<<< orphan*/  version; int /*<<< orphan*/  inode; int /*<<< orphan*/  nodetype; } ;
struct jffs2_sum_dirent_flash {int /*<<< orphan*/  name; int /*<<< orphan*/  type; int /*<<< orphan*/  nsize; int /*<<< orphan*/  ino; int /*<<< orphan*/  version; int /*<<< orphan*/  pino; int /*<<< orphan*/  offset; int /*<<< orphan*/  totlen; int /*<<< orphan*/  nodetype; } ;
struct jffs2_sb_info {int cleanmarker_size; int sector_size; int /*<<< orphan*/  erase_completion_lock; TYPE_6__* summary; } ;
struct jffs2_raw_summary {void* node_crc; void* sum_crc; void* sum_num; void* cln_mkr; void* padded; void* hdr_crc; void* totlen; void* nodetype; void* magic; } ;
struct jffs2_eraseblock {int offset; int free_size; } ;
typedef  int /*<<< orphan*/  isum ;
struct TYPE_13__ {int sum_padded; int sum_num; int /*<<< orphan*/  sum_size; struct jffs2_raw_summary* sum_buf; union jffs2_sum_mem* sum_list_head; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int JFFS2_COMPAT_MASK ; 
 int JFFS2_FEATURE_RWCOMPAT_COPY ; 
 int /*<<< orphan*/  JFFS2_MAGIC_BITMASK ; 
#define  JFFS2_NODETYPE_DIRENT 131 
#define  JFFS2_NODETYPE_INODE 130 
 int /*<<< orphan*/  JFFS2_NODETYPE_SUMMARY ; 
#define  JFFS2_NODETYPE_XATTR 129 
#define  JFFS2_NODETYPE_XREF 128 
 int /*<<< orphan*/  JFFS2_SUMMARY_DIRENT_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JFFS2_SUMMARY_INODE_SIZE ; 
 int /*<<< orphan*/  JFFS2_SUMMARY_NOSUM_SIZE ; 
 int /*<<< orphan*/  JFFS2_SUMMARY_XATTR_SIZE ; 
 int /*<<< orphan*/  JFFS2_SUMMARY_XREF_SIZE ; 
 int JFFS2_SUM_MAGIC ; 
 int /*<<< orphan*/  JFFS2_WARNING (char*,int,...) ; 
 int MAX_SUMMARY_SIZE ; 
 int REF_NORMAL ; 
 int REF_OBSOLETE ; 
 void* cpu_to_je16 (int /*<<< orphan*/ ) ; 
 void* cpu_to_je32 (int) ; 
 int crc32 (int /*<<< orphan*/ ,struct jffs2_raw_summary*,int) ; 
 int /*<<< orphan*/  dbg_summary (char*,int) ; 
 int je16_to_cpu (int /*<<< orphan*/ ) ; 
 int jffs2_flash_writev (struct jffs2_sb_info*,struct kvec*,int,int,size_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jffs2_link_node_ref (struct jffs2_sb_info*,struct jffs2_eraseblock*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jffs2_sum_disable_collecting (TYPE_6__*) ; 
 int /*<<< orphan*/  jffs2_sum_reset_collected (TYPE_6__*) ; 
 int /*<<< orphan*/  kfree (union jffs2_sum_mem*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct jffs2_raw_summary*,int,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int jffs2_sum_write_data(struct jffs2_sb_info *c, struct jffs2_eraseblock *jeb,
				uint32_t infosize, uint32_t datasize, int padsize)
{
	struct jffs2_raw_summary isum;
	union jffs2_sum_mem *temp;
	struct jffs2_sum_marker *sm;
	struct kvec vecs[2];
	uint32_t sum_ofs;
	void *wpage;
	int ret;
	size_t retlen;

	if (padsize + datasize > MAX_SUMMARY_SIZE) {
		/* It won't fit in the buffer. Abort summary for this jeb */
		jffs2_sum_disable_collecting(c->summary);

		JFFS2_WARNING("Summary too big (%d data, %d pad) in eraseblock at %08x\n",
			      datasize, padsize, jeb->offset);
		/* Non-fatal */
		return 0;
	}
	/* Is there enough space for summary? */
	if (padsize < 0) {
		/* don't try to write out summary for this jeb */
		jffs2_sum_disable_collecting(c->summary);

		JFFS2_WARNING("Not enough space for summary, padsize = %d\n",
			      padsize);
		/* Non-fatal */
		return 0;
	}

	memset(c->summary->sum_buf, 0xff, datasize);
	memset(&isum, 0, sizeof(isum));

	isum.magic = cpu_to_je16(JFFS2_MAGIC_BITMASK);
	isum.nodetype = cpu_to_je16(JFFS2_NODETYPE_SUMMARY);
	isum.totlen = cpu_to_je32(infosize);
	isum.hdr_crc = cpu_to_je32(crc32(0, &isum, sizeof(struct jffs2_unknown_node) - 4));
	isum.padded = cpu_to_je32(c->summary->sum_padded);
	isum.cln_mkr = cpu_to_je32(c->cleanmarker_size);
	isum.sum_num = cpu_to_je32(c->summary->sum_num);
	wpage = c->summary->sum_buf;

	while (c->summary->sum_num) {
		temp = c->summary->sum_list_head;

		switch (je16_to_cpu(temp->u.nodetype)) {
			case JFFS2_NODETYPE_INODE: {
				struct jffs2_sum_inode_flash *sino_ptr = wpage;

				sino_ptr->nodetype = temp->i.nodetype;
				sino_ptr->inode = temp->i.inode;
				sino_ptr->version = temp->i.version;
				sino_ptr->offset = temp->i.offset;
				sino_ptr->totlen = temp->i.totlen;

				wpage += JFFS2_SUMMARY_INODE_SIZE;

				break;
			}

			case JFFS2_NODETYPE_DIRENT: {
				struct jffs2_sum_dirent_flash *sdrnt_ptr = wpage;

				sdrnt_ptr->nodetype = temp->d.nodetype;
				sdrnt_ptr->totlen = temp->d.totlen;
				sdrnt_ptr->offset = temp->d.offset;
				sdrnt_ptr->pino = temp->d.pino;
				sdrnt_ptr->version = temp->d.version;
				sdrnt_ptr->ino = temp->d.ino;
				sdrnt_ptr->nsize = temp->d.nsize;
				sdrnt_ptr->type = temp->d.type;

				memcpy(sdrnt_ptr->name, temp->d.name,
							temp->d.nsize);

				wpage += JFFS2_SUMMARY_DIRENT_SIZE(temp->d.nsize);

				break;
			}
#ifdef CONFIG_JFFS2_FS_XATTR
			case JFFS2_NODETYPE_XATTR: {
				struct jffs2_sum_xattr_flash *sxattr_ptr = wpage;

				temp = c->summary->sum_list_head;
				sxattr_ptr->nodetype = temp->x.nodetype;
				sxattr_ptr->xid = temp->x.xid;
				sxattr_ptr->version = temp->x.version;
				sxattr_ptr->offset = temp->x.offset;
				sxattr_ptr->totlen = temp->x.totlen;

				wpage += JFFS2_SUMMARY_XATTR_SIZE;
				break;
			}
			case JFFS2_NODETYPE_XREF: {
				struct jffs2_sum_xref_flash *sxref_ptr = wpage;

				temp = c->summary->sum_list_head;
				sxref_ptr->nodetype = temp->r.nodetype;
				sxref_ptr->offset = temp->r.offset;

				wpage += JFFS2_SUMMARY_XREF_SIZE;
				break;
			}
#endif
			default : {
				if ((je16_to_cpu(temp->u.nodetype) & JFFS2_COMPAT_MASK)
				    == JFFS2_FEATURE_RWCOMPAT_COPY) {
					dbg_summary("Writing unknown RWCOMPAT_COPY node type %x\n",
						    je16_to_cpu(temp->u.nodetype));
					jffs2_sum_disable_collecting(c->summary);
				} else {
					BUG();	/* unknown node in summary information */
				}
			}
		}

		c->summary->sum_list_head = temp->u.next;
		kfree(temp);

		c->summary->sum_num--;
	}

	jffs2_sum_reset_collected(c->summary);

	wpage += padsize;

	sm = wpage;
	sm->offset = cpu_to_je32(c->sector_size - jeb->free_size);
	sm->magic = cpu_to_je32(JFFS2_SUM_MAGIC);

	isum.sum_crc = cpu_to_je32(crc32(0, c->summary->sum_buf, datasize));
	isum.node_crc = cpu_to_je32(crc32(0, &isum, sizeof(isum) - 8));

	vecs[0].iov_base = &isum;
	vecs[0].iov_len = sizeof(isum);
	vecs[1].iov_base = c->summary->sum_buf;
	vecs[1].iov_len = datasize;

	sum_ofs = jeb->offset + c->sector_size - jeb->free_size;

	dbg_summary("writing out data to flash to pos : 0x%08x\n", sum_ofs);

	ret = jffs2_flash_writev(c, vecs, 2, sum_ofs, &retlen, 0);

	if (ret || (retlen != infosize)) {

		JFFS2_WARNING("Write of %u bytes at 0x%08x failed. returned %d, retlen %zd\n",
			      infosize, sum_ofs, ret, retlen);

		if (retlen) {
			/* Waste remaining space */
			spin_lock(&c->erase_completion_lock);
			jffs2_link_node_ref(c, jeb, sum_ofs | REF_OBSOLETE, infosize, NULL);
			spin_unlock(&c->erase_completion_lock);
		}

		c->summary->sum_size = JFFS2_SUMMARY_NOSUM_SIZE;

		return 0;
	}

	spin_lock(&c->erase_completion_lock);
	jffs2_link_node_ref(c, jeb, sum_ofs | REF_NORMAL, infosize, NULL);
	spin_unlock(&c->erase_completion_lock);

	return 0;
}