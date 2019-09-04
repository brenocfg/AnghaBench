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
typedef  int /*<<< orphan*/  u8 ;
struct hfs_bnode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hfs_bnode_write (struct hfs_bnode*,int /*<<< orphan*/ *,int,int) ; 

void hfs_bnode_write_u8(struct hfs_bnode *node, int off, u8 data)
{
	// optimize later...
	hfs_bnode_write(node, &data, off, 1);
}