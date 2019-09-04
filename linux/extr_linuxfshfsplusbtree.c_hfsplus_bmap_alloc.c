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
typedef  int u8 ;
typedef  int u32 ;
typedef  unsigned int u16 ;
struct page {int dummy; } ;
struct inode {int i_size; } ;
struct hfsplus_inode_info {int phys_size; int alloc_blocks; int fs_blocks; } ;
struct hfs_btree {int free_nodes; int node_size_shift; int node_count; struct inode* inode; int /*<<< orphan*/  sb; } ;
struct hfs_bnode {int next; struct page** page; scalar_t__ page_offset; } ;
typedef  int loff_t ;
struct TYPE_2__ {int alloc_blksz_shift; int fs_shift; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNODE_MOD ; 
 struct hfs_bnode* ERR_PTR (int) ; 
 struct hfsplus_inode_info* HFSPLUS_I (struct inode*) ; 
 TYPE_1__* HFSPLUS_SB (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct hfs_bnode*) ; 
 unsigned int PAGE_MASK ; 
 unsigned int PAGE_SHIFT ; 
 unsigned int PAGE_SIZE ; 
 struct hfs_bnode* hfs_bmap_new_bmap (struct hfs_bnode*,int) ; 
 struct hfs_bnode* hfs_bnode_create (struct hfs_btree*,int) ; 
 struct hfs_bnode* hfs_bnode_find (struct hfs_btree*,int) ; 
 int /*<<< orphan*/  hfs_bnode_need_zeroout (struct hfs_btree*) ; 
 int /*<<< orphan*/  hfs_bnode_put (struct hfs_bnode*) ; 
 unsigned int hfs_brec_lenoff (struct hfs_bnode*,int,unsigned int*) ; 
 int /*<<< orphan*/  hfs_dbg (int /*<<< orphan*/ ,char*) ; 
 int hfsplus_file_extend (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_set_bytes (struct inode*,int) ; 
 int* kmap (struct page*) ; 
 int /*<<< orphan*/  kunmap (struct page*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 int /*<<< orphan*/  set_page_dirty (struct page*) ; 

struct hfs_bnode *hfs_bmap_alloc(struct hfs_btree *tree)
{
	struct hfs_bnode *node, *next_node;
	struct page **pagep;
	u32 nidx, idx;
	unsigned off;
	u16 off16;
	u16 len;
	u8 *data, byte, m;
	int i;

	while (!tree->free_nodes) {
		struct inode *inode = tree->inode;
		struct hfsplus_inode_info *hip = HFSPLUS_I(inode);
		u32 count;
		int res;

		res = hfsplus_file_extend(inode, hfs_bnode_need_zeroout(tree));
		if (res)
			return ERR_PTR(res);
		hip->phys_size = inode->i_size =
			(loff_t)hip->alloc_blocks <<
				HFSPLUS_SB(tree->sb)->alloc_blksz_shift;
		hip->fs_blocks =
			hip->alloc_blocks << HFSPLUS_SB(tree->sb)->fs_shift;
		inode_set_bytes(inode, inode->i_size);
		count = inode->i_size >> tree->node_size_shift;
		tree->free_nodes = count - tree->node_count;
		tree->node_count = count;
	}

	nidx = 0;
	node = hfs_bnode_find(tree, nidx);
	if (IS_ERR(node))
		return node;
	len = hfs_brec_lenoff(node, 2, &off16);
	off = off16;

	off += node->page_offset;
	pagep = node->page + (off >> PAGE_SHIFT);
	data = kmap(*pagep);
	off &= ~PAGE_MASK;
	idx = 0;

	for (;;) {
		while (len) {
			byte = data[off];
			if (byte != 0xff) {
				for (m = 0x80, i = 0; i < 8; m >>= 1, i++) {
					if (!(byte & m)) {
						idx += i;
						data[off] |= m;
						set_page_dirty(*pagep);
						kunmap(*pagep);
						tree->free_nodes--;
						mark_inode_dirty(tree->inode);
						hfs_bnode_put(node);
						return hfs_bnode_create(tree,
							idx);
					}
				}
			}
			if (++off >= PAGE_SIZE) {
				kunmap(*pagep);
				data = kmap(*++pagep);
				off = 0;
			}
			idx += 8;
			len--;
		}
		kunmap(*pagep);
		nidx = node->next;
		if (!nidx) {
			hfs_dbg(BNODE_MOD, "create new bmap node\n");
			next_node = hfs_bmap_new_bmap(node, idx);
		} else
			next_node = hfs_bnode_find(tree, nidx);
		hfs_bnode_put(node);
		if (IS_ERR(next_node))
			return next_node;
		node = next_node;

		len = hfs_brec_lenoff(node, 0, &off16);
		off = off16;
		off += node->page_offset;
		pagep = node->page + (off >> PAGE_SHIFT);
		data = kmap(*pagep);
		off &= ~PAGE_MASK;
	}
}