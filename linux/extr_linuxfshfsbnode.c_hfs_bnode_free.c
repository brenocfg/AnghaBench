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
struct hfs_bnode {scalar_t__* page; TYPE_1__* tree; } ;
struct TYPE_2__ {int pages_per_bnode; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct hfs_bnode*) ; 
 int /*<<< orphan*/  put_page (scalar_t__) ; 

void hfs_bnode_free(struct hfs_bnode *node)
{
	int i;

	for (i = 0; i < node->tree->pages_per_bnode; i++)
		if (node->page[i])
			put_page(node->page[i]);
	kfree(node);
}