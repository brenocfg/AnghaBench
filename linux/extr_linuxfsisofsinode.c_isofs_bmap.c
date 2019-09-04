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
struct inode {int dummy; } ;
struct buffer_head {int b_blocknr; scalar_t__ b_state; } ;
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */
 int isofs_get_block (struct inode*,int /*<<< orphan*/ ,struct buffer_head*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int isofs_bmap(struct inode *inode, sector_t block)
{
	struct buffer_head dummy;
	int error;

	dummy.b_state = 0;
	dummy.b_blocknr = -1000;
	error = isofs_get_block(inode, block, &dummy, 0);
	if (!error)
		return dummy.b_blocknr;
	return 0;
}