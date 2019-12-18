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
struct ocfs2_dx_entry_list {TYPE_1__* de_entries; int /*<<< orphan*/  de_num_used; } ;
struct ocfs2_dx_leaf {struct ocfs2_dx_entry_list dl_list; } ;
struct TYPE_2__ {int /*<<< orphan*/  dx_major_hash; } ;

/* Variables and functions */
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ocfs2_dx_leaf_same_major(struct ocfs2_dx_leaf *dx_leaf)
{
	struct ocfs2_dx_entry_list *dl_list = &dx_leaf->dl_list;
	int i, num = le16_to_cpu(dl_list->de_num_used);

	for (i = 0; i < (num - 1); i++) {
		if (le32_to_cpu(dl_list->de_entries[i].dx_major_hash) !=
		    le32_to_cpu(dl_list->de_entries[i + 1].dx_major_hash))
			return 0;
	}

	return 1;
}