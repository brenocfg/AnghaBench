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
struct page {int dummy; } ;
struct TYPE_2__ {void* flag; void* ino; void* nid; } ;
struct f2fs_node {TYPE_1__ footer; } ;
typedef  unsigned int nid_t ;

/* Variables and functions */
 struct f2fs_node* F2FS_NODE (struct page*) ; 
 unsigned int OFFSET_BIT_MASK ; 
 unsigned int OFFSET_BIT_SHIFT ; 
 void* cpu_to_le32 (unsigned int) ; 
 unsigned int le32_to_cpu (void*) ; 
 int /*<<< orphan*/  memset (struct f2fs_node*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void fill_node_footer(struct page *page, nid_t nid,
				nid_t ino, unsigned int ofs, bool reset)
{
	struct f2fs_node *rn = F2FS_NODE(page);
	unsigned int old_flag = 0;

	if (reset)
		memset(rn, 0, sizeof(*rn));
	else
		old_flag = le32_to_cpu(rn->footer.flag);

	rn->footer.nid = cpu_to_le32(nid);
	rn->footer.ino = cpu_to_le32(ino);

	/* should remain old flag bits such as COLD_BIT_SHIFT */
	rn->footer.flag = cpu_to_le32((ofs << OFFSET_BIT_SHIFT) |
					(old_flag & OFFSET_BIT_MASK));
}