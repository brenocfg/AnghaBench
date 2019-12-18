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
struct TYPE_2__ {int /*<<< orphan*/  cp_ver; } ;
struct f2fs_node {TYPE_1__ footer; } ;
typedef  int /*<<< orphan*/  __u64 ;

/* Variables and functions */
 struct f2fs_node* F2FS_NODE (struct page*) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline __u64 cpver_of_node(struct page *node_page)
{
	struct f2fs_node *rn = F2FS_NODE(node_page);
	return le64_to_cpu(rn->footer.cp_ver);
}