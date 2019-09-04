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
typedef  int u16 ;
struct hfs_bnode {TYPE_1__* tree; } ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_2__ {int node_size; } ;

/* Variables and functions */
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hfs_bnode_read (struct hfs_bnode*,int /*<<< orphan*/ *,int,int) ; 

u16 hfs_brec_lenoff(struct hfs_bnode *node, u16 rec, u16 *off)
{
	__be16 retval[2];
	u16 dataoff;

	dataoff = node->tree->node_size - (rec + 2) * 2;
	hfs_bnode_read(node, retval, dataoff, 4);
	*off = be16_to_cpu(retval[1]);
	return be16_to_cpu(retval[0]) - *off;
}