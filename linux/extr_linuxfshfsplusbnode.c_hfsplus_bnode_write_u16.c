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
typedef  int /*<<< orphan*/  u16 ;
struct hfs_bnode {int dummy; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hfs_bnode_write (struct hfs_bnode*,int /*<<< orphan*/ *,int,int) ; 

void hfs_bnode_write_u16(struct hfs_bnode *node, int off, u16 data)
{
	__be16 v = cpu_to_be16(data);
	/* TODO: optimize later... */
	hfs_bnode_write(node, &v, off, 2);
}