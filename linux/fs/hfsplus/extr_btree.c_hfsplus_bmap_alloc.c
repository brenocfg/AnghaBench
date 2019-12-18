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
typedef  int u8 ;
typedef  int u32 ;
typedef  unsigned int u16 ;
struct page {int dummy; } ;
struct hfs_btree {int /*<<< orphan*/  inode; int /*<<< orphan*/  free_nodes; } ;
struct hfs_bnode {int next; struct page** page; scalar_t__ page_offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNODE_MOD ; 
 struct hfs_bnode* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct hfs_bnode*) ; 
 unsigned int PAGE_MASK ; 
 unsigned int PAGE_SHIFT ; 
 unsigned int PAGE_SIZE ; 
 struct hfs_bnode* hfs_bmap_new_bmap (struct hfs_bnode*,int) ; 
 int hfs_bmap_reserve (struct hfs_btree*,int) ; 
 struct hfs_bnode* hfs_bnode_create (struct hfs_btree*,int) ; 
 struct hfs_bnode* hfs_bnode_find (struct hfs_btree*,int) ; 
 int /*<<< orphan*/  hfs_bnode_put (struct hfs_bnode*) ; 
 unsigned int hfs_brec_lenoff (struct hfs_bnode*,int,unsigned int*) ; 
 int /*<<< orphan*/  hfs_dbg (int /*<<< orphan*/ ,char*) ; 
 int* kmap (struct page*) ; 
 int /*<<< orphan*/  kunmap (struct page*) ; 
 int /*<<< orphan*/  mark_inode_dirty (int /*<<< orphan*/ ) ; 
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
	int i, res;

	res = hfs_bmap_reserve(tree, 1);
	if (res)
		return ERR_PTR(res);

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