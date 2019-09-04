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
struct page {int dummy; } ;
struct node_footer {int dummy; } ;
struct f2fs_node {int /*<<< orphan*/  footer; } ;

/* Variables and functions */
 struct f2fs_node* F2FS_NODE (struct page*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline void copy_node_footer(struct page *dst, struct page *src)
{
	struct f2fs_node *src_rn = F2FS_NODE(src);
	struct f2fs_node *dst_rn = F2FS_NODE(dst);
	memcpy(&dst_rn->footer, &src_rn->footer, sizeof(struct node_footer));
}