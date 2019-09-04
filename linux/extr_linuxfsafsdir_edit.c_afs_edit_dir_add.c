#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int valid; scalar_t__* name; void* unique; void* vnode; scalar_t__ hash_next; scalar_t__* unused; } ;
union afs_xdr_dirent {TYPE_3__ u; } ;
struct TYPE_9__ {int* alloc_ctrs; } ;
struct TYPE_8__ {int /*<<< orphan*/  magic; int /*<<< orphan*/  npages; } ;
union afs_xdr_dir_block {TYPE_2__ meta; union afs_xdr_dirent* dirents; TYPE_1__ hdr; } ;
struct qstr {int len; int /*<<< orphan*/  name; } ;
struct page {int dummy; } ;
struct afs_xdr_dir_page {union afs_xdr_dir_block* blocks; } ;
struct TYPE_11__ {TYPE_7__* i_mapping; } ;
struct afs_vnode {int /*<<< orphan*/  flags; TYPE_4__ vfs_inode; } ;
struct afs_fid {int /*<<< orphan*/  unique; int /*<<< orphan*/  vnode; } ;
typedef  unsigned int pgoff_t ;
typedef  int loff_t ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  enum afs_edit_dir_reason { ____Placeholder_afs_edit_dir_reason } afs_edit_dir_reason ;
struct TYPE_12__ {int /*<<< orphan*/  gfp_mask; } ;

/* Variables and functions */
 unsigned int AFS_DIR_BLOCKS_PER_PAGE ; 
 unsigned int AFS_DIR_BLOCKS_WITH_CTR ; 
 int AFS_DIR_BLOCK_SIZE ; 
 unsigned int AFS_DIR_DIRENT_SIZE ; 
 int AFS_DIR_MAX_BLOCKS ; 
 int AFS_DIR_RESV_BLOCKS0 ; 
 int /*<<< orphan*/  AFS_VNODE_DIR_VALID ; 
 int /*<<< orphan*/  PagePrivate (struct page*) ; 
 int /*<<< orphan*/  SetPagePrivate (struct page*) ; 
 int /*<<< orphan*/  _debug (char*,unsigned int,...) ; 
 int /*<<< orphan*/  _enter (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _leave (char*) ; 
 int /*<<< orphan*/  afs_edit_dir_create ; 
 int /*<<< orphan*/  afs_edit_dir_create_error ; 
 int /*<<< orphan*/  afs_edit_dir_create_inval ; 
 int /*<<< orphan*/  afs_edit_dir_create_nospc ; 
 int /*<<< orphan*/  afs_edit_init_block (union afs_xdr_dir_block*,union afs_xdr_dir_block*,unsigned int) ; 
 int afs_find_contig_bits (union afs_xdr_dir_block*,unsigned int) ; 
 int /*<<< orphan*/  afs_set_contig_bits (union afs_xdr_dir_block*,int,unsigned int) ; 
 int /*<<< orphan*/  afs_stat_v (struct afs_vnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct page* find_or_create_page (TYPE_7__*,unsigned int,int /*<<< orphan*/ ) ; 
 void* htonl (int /*<<< orphan*/ ) ; 
 int i_size_read (TYPE_4__*) ; 
 int /*<<< orphan*/  i_size_write (TYPE_4__*,int) ; 
 int /*<<< orphan*/  inode_inc_iversion_raw (TYPE_4__*) ; 
 struct afs_xdr_dir_page* kmap (struct page*) ; 
 int /*<<< orphan*/  kunmap (struct page*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  n_dir_cr ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 unsigned int round_up (int,unsigned int) ; 
 int /*<<< orphan*/  set_page_private (struct page*,int) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_afs_edit_dir (struct afs_vnode*,int,int /*<<< orphan*/ ,unsigned int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

void afs_edit_dir_add(struct afs_vnode *vnode,
		      struct qstr *name, struct afs_fid *new_fid,
		      enum afs_edit_dir_reason why)
{
	union afs_xdr_dir_block *meta, *block;
	struct afs_xdr_dir_page *meta_page, *dir_page;
	union afs_xdr_dirent *de;
	struct page *page0, *page;
	unsigned int need_slots, nr_blocks, b;
	pgoff_t index;
	loff_t i_size;
	gfp_t gfp;
	int slot;

	_enter(",,{%d,%s},", name->len, name->name);

	i_size = i_size_read(&vnode->vfs_inode);
	if (i_size > AFS_DIR_BLOCK_SIZE * AFS_DIR_MAX_BLOCKS ||
	    (i_size & (AFS_DIR_BLOCK_SIZE - 1))) {
		clear_bit(AFS_VNODE_DIR_VALID, &vnode->flags);
		return;
	}

	gfp = vnode->vfs_inode.i_mapping->gfp_mask;
	page0 = find_or_create_page(vnode->vfs_inode.i_mapping, 0, gfp);
	if (!page0) {
		clear_bit(AFS_VNODE_DIR_VALID, &vnode->flags);
		_leave(" [fgp]");
		return;
	}

	/* Work out how many slots we're going to need. */
	need_slots = round_up(12 + name->len + 1 + 4, AFS_DIR_DIRENT_SIZE);
	need_slots /= AFS_DIR_DIRENT_SIZE;

	meta_page = kmap(page0);
	meta = &meta_page->blocks[0];
	if (i_size == 0)
		goto new_directory;
	nr_blocks = i_size / AFS_DIR_BLOCK_SIZE;

	/* Find a block that has sufficient slots available.  Each VM page
	 * contains two or more directory blocks.
	 */
	for (b = 0; b < nr_blocks + 1; b++) {
		/* If the directory extended into a new page, then we need to
		 * tack a new page on the end.
		 */
		index = b / AFS_DIR_BLOCKS_PER_PAGE;
		if (index == 0) {
			page = page0;
			dir_page = meta_page;
		} else {
			if (nr_blocks >= AFS_DIR_MAX_BLOCKS)
				goto error;
			gfp = vnode->vfs_inode.i_mapping->gfp_mask;
			page = find_or_create_page(vnode->vfs_inode.i_mapping,
						   index, gfp);
			if (!page)
				goto error;
			if (!PagePrivate(page)) {
				set_page_private(page, 1);
				SetPagePrivate(page);
			}
			dir_page = kmap(page);
		}

		/* Abandon the edit if we got a callback break. */
		if (!test_bit(AFS_VNODE_DIR_VALID, &vnode->flags))
			goto invalidated;

		block = &dir_page->blocks[b % AFS_DIR_BLOCKS_PER_PAGE];

		_debug("block %u: %2u %3u %u",
		       b,
		       (b < AFS_DIR_BLOCKS_WITH_CTR) ? meta->meta.alloc_ctrs[b] : 99,
		       ntohs(block->hdr.npages),
		       ntohs(block->hdr.magic));

		/* Initialise the block if necessary. */
		if (b == nr_blocks) {
			_debug("init %u", b);
			afs_edit_init_block(meta, block, b);
			i_size_write(&vnode->vfs_inode, (b + 1) * AFS_DIR_BLOCK_SIZE);
		}

		/* Only lower dir pages have a counter in the header. */
		if (b >= AFS_DIR_BLOCKS_WITH_CTR ||
		    meta->meta.alloc_ctrs[b] >= need_slots) {
			/* We need to try and find one or more consecutive
			 * slots to hold the entry.
			 */
			slot = afs_find_contig_bits(block, need_slots);
			if (slot >= 0) {
				_debug("slot %u", slot);
				goto found_space;
			}
		}

		if (page != page0) {
			unlock_page(page);
			kunmap(page);
			put_page(page);
		}
	}

	/* There are no spare slots of sufficient size, yet the operation
	 * succeeded.  Download the directory again.
	 */
	trace_afs_edit_dir(vnode, why, afs_edit_dir_create_nospc, 0, 0, 0, 0, name->name);
	clear_bit(AFS_VNODE_DIR_VALID, &vnode->flags);
	goto out_unmap;

new_directory:
	afs_edit_init_block(meta, meta, 0);
	i_size = AFS_DIR_BLOCK_SIZE;
	i_size_write(&vnode->vfs_inode, i_size);
	slot = AFS_DIR_RESV_BLOCKS0;
	page = page0;
	block = meta;
	nr_blocks = 1;
	b = 0;

found_space:
	/* Set the dirent slot. */
	trace_afs_edit_dir(vnode, why, afs_edit_dir_create, b, slot,
			   new_fid->vnode, new_fid->unique, name->name);
	de = &block->dirents[slot];
	de->u.valid	= 1;
	de->u.unused[0]	= 0;
	de->u.hash_next	= 0; // TODO: Really need to maintain this
	de->u.vnode	= htonl(new_fid->vnode);
	de->u.unique	= htonl(new_fid->unique);
	memcpy(de->u.name, name->name, name->len + 1);
	de->u.name[name->len] = 0;

	/* Adjust the bitmap. */
	afs_set_contig_bits(block, slot, need_slots);
	if (page != page0) {
		unlock_page(page);
		kunmap(page);
		put_page(page);
	}

	/* Adjust the allocation counter. */
	if (b < AFS_DIR_BLOCKS_WITH_CTR)
		meta->meta.alloc_ctrs[b] -= need_slots;

	inode_inc_iversion_raw(&vnode->vfs_inode);
	afs_stat_v(vnode, n_dir_cr);
	_debug("Insert %s in %u[%u]", name->name, b, slot);

out_unmap:
	unlock_page(page0);
	kunmap(page0);
	put_page(page0);
	_leave("");
	return;

invalidated:
	trace_afs_edit_dir(vnode, why, afs_edit_dir_create_inval, 0, 0, 0, 0, name->name);
	clear_bit(AFS_VNODE_DIR_VALID, &vnode->flags);
	if (page != page0) {
		kunmap(page);
		put_page(page);
	}
	goto out_unmap;

error:
	trace_afs_edit_dir(vnode, why, afs_edit_dir_create_error, 0, 0, 0, 0, name->name);
	clear_bit(AFS_VNODE_DIR_VALID, &vnode->flags);
	goto out_unmap;
}