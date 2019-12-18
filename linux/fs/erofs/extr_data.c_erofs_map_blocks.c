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
struct inode {int dummy; } ;
struct erofs_map_blocks {int /*<<< orphan*/ * mpage; } ;
struct TYPE_2__ {int /*<<< orphan*/  datalayout; } ;

/* Variables and functions */
 TYPE_1__* EROFS_I (struct inode*) ; 
 scalar_t__ erofs_inode_is_data_compressed (int /*<<< orphan*/ ) ; 
 int erofs_map_blocks_flatmode (struct inode*,struct erofs_map_blocks*,int) ; 
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ *) ; 
 int z_erofs_map_blocks_iter (struct inode*,struct erofs_map_blocks*,int) ; 

int erofs_map_blocks(struct inode *inode,
		     struct erofs_map_blocks *map, int flags)
{
	if (erofs_inode_is_data_compressed(EROFS_I(inode)->datalayout)) {
		int err = z_erofs_map_blocks_iter(inode, map, flags);

		if (map->mpage) {
			put_page(map->mpage);
			map->mpage = NULL;
		}
		return err;
	}
	return erofs_map_blocks_flatmode(inode, map, flags);
}