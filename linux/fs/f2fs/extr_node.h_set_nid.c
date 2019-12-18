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
struct page {int dummy; } ;
struct TYPE_4__ {void** nid; } ;
struct TYPE_3__ {void** i_nid; } ;
struct f2fs_node {TYPE_2__ in; TYPE_1__ i; } ;
typedef  int /*<<< orphan*/  nid_t ;

/* Variables and functions */
 struct f2fs_node* F2FS_NODE (struct page*) ; 
 int /*<<< orphan*/  NODE ; 
 int NODE_DIR1_BLOCK ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_wait_on_page_writeback (struct page*,int /*<<< orphan*/ ,int,int) ; 
 int set_page_dirty (struct page*) ; 

__attribute__((used)) static inline int set_nid(struct page *p, int off, nid_t nid, bool i)
{
	struct f2fs_node *rn = F2FS_NODE(p);

	f2fs_wait_on_page_writeback(p, NODE, true, true);

	if (i)
		rn->i.i_nid[off - NODE_DIR1_BLOCK] = cpu_to_le32(nid);
	else
		rn->in.nid[off] = cpu_to_le32(nid);
	return set_page_dirty(p);
}