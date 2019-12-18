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
struct hfs_find_data {int /*<<< orphan*/  search_key; int /*<<< orphan*/  key; } ;
struct hfs_bnode {TYPE_1__* tree; } ;
struct TYPE_2__ {int (* keycmp ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int hfs_find_rec_by_key(struct hfs_bnode *bnode,
				struct hfs_find_data *fd,
				int *begin,
				int *end,
				int *cur_rec)
{
	int cmpval;

	cmpval = bnode->tree->keycmp(fd->key, fd->search_key);
	if (!cmpval) {
		(*end) = (*cur_rec);
		return 1;
	}
	if (cmpval < 0)
		(*begin) = (*cur_rec) + 1;
	else
		*(end) = (*cur_rec) - 1;

	return 0;
}