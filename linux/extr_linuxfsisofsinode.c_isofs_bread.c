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
struct inode {int /*<<< orphan*/  i_sb; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  isofs_bmap (struct inode*,int /*<<< orphan*/ ) ; 
 struct buffer_head* sb_bread (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct buffer_head *isofs_bread(struct inode *inode, sector_t block)
{
	sector_t blknr = isofs_bmap(inode, block);
	if (!blknr)
		return NULL;
	return sb_bread(inode->i_sb, blknr);
}