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
struct inode {int /*<<< orphan*/  i_mapping; int /*<<< orphan*/  i_sb; } ;
struct bmap {int dummy; } ;
struct TYPE_2__ {struct bmap* bmap; } ;

/* Variables and functions */
 TYPE_1__* JFS_SBI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbSync (struct inode*) ; 
 scalar_t__ isReadOnly (struct inode*) ; 
 int /*<<< orphan*/  kfree (struct bmap*) ; 
 int /*<<< orphan*/  truncate_inode_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int dbUnmount(struct inode *ipbmap, int mounterror)
{
	struct bmap *bmp = JFS_SBI(ipbmap->i_sb)->bmap;

	if (!(mounterror || isReadOnly(ipbmap)))
		dbSync(ipbmap);

	/*
	 * Invalidate the page cache buffers
	 */
	truncate_inode_pages(ipbmap->i_mapping, 0);

	/* free the memory for the in-memory bmap. */
	kfree(bmp);

	return (0);
}