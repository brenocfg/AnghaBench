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
typedef  int uint32_t ;
typedef  int uint16_t ;
struct jffs2_sum_unknown_flash {int /*<<< orphan*/  nodetype; } ;
struct jffs2_sum_inode_flash {int /*<<< orphan*/  version; int /*<<< orphan*/  totlen; int /*<<< orphan*/  offset; int /*<<< orphan*/  inode; } ;
struct jffs2_sum_dirent_flash {int nsize; int /*<<< orphan*/  version; int /*<<< orphan*/  type; int /*<<< orphan*/  ino; int /*<<< orphan*/  totlen; int /*<<< orphan*/  offset; int /*<<< orphan*/  pino; int /*<<< orphan*/  name; } ;
struct jffs2_sb_info {scalar_t__ sector_size; int /*<<< orphan*/  dirty_size; int /*<<< orphan*/  used_size; scalar_t__ free_size; int /*<<< orphan*/  wasted_size; } ;
struct jffs2_raw_summary {int /*<<< orphan*/  sum_num; void* sum; } ;
struct jffs2_inode_cache {int /*<<< orphan*/  scan_dents; } ;
struct jffs2_full_dirent {int version; int ino; int /*<<< orphan*/  type; int /*<<< orphan*/ * name; int /*<<< orphan*/  nhash; int /*<<< orphan*/ * next; int /*<<< orphan*/  raw; } ;
struct jffs2_eraseblock {scalar_t__ free_size; int /*<<< orphan*/  dirty_size; int /*<<< orphan*/  used_size; int /*<<< orphan*/  wasted_size; int /*<<< orphan*/  offset; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int ENOTRECOVERABLE ; 
 int JFFS2_COMPAT_MASK ; 
 int JFFS2_FEATURE_INCOMPAT ; 
#define  JFFS2_NODETYPE_DIRENT 129 
#define  JFFS2_NODETYPE_INODE 128 
 int /*<<< orphan*/  JFFS2_NOTICE (char*) ; 
 int /*<<< orphan*/  JFFS2_SUMMARY_DIRENT_SIZE (int) ; 
 int /*<<< orphan*/  JFFS2_SUMMARY_INODE_SIZE ; 
 int /*<<< orphan*/  JFFS2_WARNING (char*,int) ; 
 int /*<<< orphan*/  PAD (int) ; 
 int REF_UNCHECKED ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  dbg_summary (char*,int,...) ; 
 int /*<<< orphan*/  full_name_hash (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int je16_to_cpu (int /*<<< orphan*/ ) ; 
 int je32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jffs2_add_fd_to_list (struct jffs2_sb_info*,struct jffs2_full_dirent*,int /*<<< orphan*/ *) ; 
 struct jffs2_full_dirent* jffs2_alloc_full_dirent (int) ; 
 int /*<<< orphan*/  jffs2_free_full_dirent (struct jffs2_full_dirent*) ; 
 int /*<<< orphan*/  jffs2_free_jeb_node_refs (struct jffs2_sb_info*,struct jffs2_eraseblock*) ; 
 int jffs2_prealloc_raw_node_refs (struct jffs2_sb_info*,struct jffs2_eraseblock*,int) ; 
 struct jffs2_inode_cache* jffs2_scan_make_ino_cache (struct jffs2_sb_info*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,...) ; 
 int strnlen (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sum_link_node_ref (struct jffs2_sb_info*,struct jffs2_eraseblock*,int,int /*<<< orphan*/ ,struct jffs2_inode_cache*) ; 

__attribute__((used)) static int jffs2_sum_process_sum_data(struct jffs2_sb_info *c, struct jffs2_eraseblock *jeb,
				struct jffs2_raw_summary *summary, uint32_t *pseudo_random)
{
	struct jffs2_inode_cache *ic;
	struct jffs2_full_dirent *fd;
	void *sp;
	int i, ino;
	int err;

	sp = summary->sum;

	for (i=0; i<je32_to_cpu(summary->sum_num); i++) {
		dbg_summary("processing summary index %d\n", i);

		cond_resched();

		/* Make sure there's a spare ref for dirty space */
		err = jffs2_prealloc_raw_node_refs(c, jeb, 2);
		if (err)
			return err;

		switch (je16_to_cpu(((struct jffs2_sum_unknown_flash *)sp)->nodetype)) {
			case JFFS2_NODETYPE_INODE: {
				struct jffs2_sum_inode_flash *spi;
				spi = sp;

				ino = je32_to_cpu(spi->inode);

				dbg_summary("Inode at 0x%08x-0x%08x\n",
					    jeb->offset + je32_to_cpu(spi->offset),
					    jeb->offset + je32_to_cpu(spi->offset) + je32_to_cpu(spi->totlen));

				ic = jffs2_scan_make_ino_cache(c, ino);
				if (!ic) {
					JFFS2_NOTICE("scan_make_ino_cache failed\n");
					return -ENOMEM;
				}

				sum_link_node_ref(c, jeb, je32_to_cpu(spi->offset) | REF_UNCHECKED,
						  PAD(je32_to_cpu(spi->totlen)), ic);

				*pseudo_random += je32_to_cpu(spi->version);

				sp += JFFS2_SUMMARY_INODE_SIZE;

				break;
			}

			case JFFS2_NODETYPE_DIRENT: {
				struct jffs2_sum_dirent_flash *spd;
				int checkedlen;
				spd = sp;

				dbg_summary("Dirent at 0x%08x-0x%08x\n",
					    jeb->offset + je32_to_cpu(spd->offset),
					    jeb->offset + je32_to_cpu(spd->offset) + je32_to_cpu(spd->totlen));


				/* This should never happen, but https://dev.laptop.org/ticket/4184 */
				checkedlen = strnlen(spd->name, spd->nsize);
				if (!checkedlen) {
					pr_err("Dirent at %08x has zero at start of name. Aborting mount.\n",
					       jeb->offset +
					       je32_to_cpu(spd->offset));
					return -EIO;
				}
				if (checkedlen < spd->nsize) {
					pr_err("Dirent at %08x has zeroes in name. Truncating to %d chars\n",
					       jeb->offset +
					       je32_to_cpu(spd->offset),
					       checkedlen);
				}


				fd = jffs2_alloc_full_dirent(checkedlen+1);
				if (!fd)
					return -ENOMEM;

				memcpy(&fd->name, spd->name, checkedlen);
				fd->name[checkedlen] = 0;

				ic = jffs2_scan_make_ino_cache(c, je32_to_cpu(spd->pino));
				if (!ic) {
					jffs2_free_full_dirent(fd);
					return -ENOMEM;
				}

				fd->raw = sum_link_node_ref(c, jeb,  je32_to_cpu(spd->offset) | REF_UNCHECKED,
							    PAD(je32_to_cpu(spd->totlen)), ic);

				fd->next = NULL;
				fd->version = je32_to_cpu(spd->version);
				fd->ino = je32_to_cpu(spd->ino);
				fd->nhash = full_name_hash(NULL, fd->name, checkedlen);
				fd->type = spd->type;

				jffs2_add_fd_to_list(c, fd, &ic->scan_dents);

				*pseudo_random += je32_to_cpu(spd->version);

				sp += JFFS2_SUMMARY_DIRENT_SIZE(spd->nsize);

				break;
			}
#ifdef CONFIG_JFFS2_FS_XATTR
			case JFFS2_NODETYPE_XATTR: {
				struct jffs2_xattr_datum *xd;
				struct jffs2_sum_xattr_flash *spx;

				spx = (struct jffs2_sum_xattr_flash *)sp;
				dbg_summary("xattr at %#08x-%#08x (xid=%u, version=%u)\n", 
					    jeb->offset + je32_to_cpu(spx->offset),
					    jeb->offset + je32_to_cpu(spx->offset) + je32_to_cpu(spx->totlen),
					    je32_to_cpu(spx->xid), je32_to_cpu(spx->version));

				xd = jffs2_setup_xattr_datum(c, je32_to_cpu(spx->xid),
								je32_to_cpu(spx->version));
				if (IS_ERR(xd))
					return PTR_ERR(xd);
				if (xd->version > je32_to_cpu(spx->version)) {
					/* node is not the newest one */
					struct jffs2_raw_node_ref *raw
						= sum_link_node_ref(c, jeb, je32_to_cpu(spx->offset) | REF_UNCHECKED,
								    PAD(je32_to_cpu(spx->totlen)), NULL);
					raw->next_in_ino = xd->node->next_in_ino;
					xd->node->next_in_ino = raw;
				} else {
					xd->version = je32_to_cpu(spx->version);
					sum_link_node_ref(c, jeb, je32_to_cpu(spx->offset) | REF_UNCHECKED,
							  PAD(je32_to_cpu(spx->totlen)), (void *)xd);
				}
				*pseudo_random += je32_to_cpu(spx->xid);
				sp += JFFS2_SUMMARY_XATTR_SIZE;

				break;
			}
			case JFFS2_NODETYPE_XREF: {
				struct jffs2_xattr_ref *ref;
				struct jffs2_sum_xref_flash *spr;

				spr = (struct jffs2_sum_xref_flash *)sp;
				dbg_summary("xref at %#08x-%#08x\n",
					    jeb->offset + je32_to_cpu(spr->offset),
					    jeb->offset + je32_to_cpu(spr->offset) + 
					    (uint32_t)PAD(sizeof(struct jffs2_raw_xref)));

				ref = jffs2_alloc_xattr_ref();
				if (!ref) {
					JFFS2_NOTICE("allocation of xattr_datum failed\n");
					return -ENOMEM;
				}
				ref->next = c->xref_temp;
				c->xref_temp = ref;

				sum_link_node_ref(c, jeb, je32_to_cpu(spr->offset) | REF_UNCHECKED,
						  PAD(sizeof(struct jffs2_raw_xref)), (void *)ref);

				*pseudo_random += ref->node->flash_offset;
				sp += JFFS2_SUMMARY_XREF_SIZE;

				break;
			}
#endif
			default : {
				uint16_t nodetype = je16_to_cpu(((struct jffs2_sum_unknown_flash *)sp)->nodetype);
				JFFS2_WARNING("Unsupported node type %x found in summary! Exiting...\n", nodetype);
				if ((nodetype & JFFS2_COMPAT_MASK) == JFFS2_FEATURE_INCOMPAT)
					return -EIO;

				/* For compatible node types, just fall back to the full scan */
				c->wasted_size -= jeb->wasted_size;
				c->free_size += c->sector_size - jeb->free_size;
				c->used_size -= jeb->used_size;
				c->dirty_size -= jeb->dirty_size;
				jeb->wasted_size = jeb->used_size = jeb->dirty_size = 0;
				jeb->free_size = c->sector_size;

				jffs2_free_jeb_node_refs(c, jeb);
				return -ENOTRECOVERABLE;
			}
		}
	}
	return 0;
}