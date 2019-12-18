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
struct pnfs_block_layout {int dummy; } ;
struct pnfs_block_extent {size_t be_length; size_t be_f_offset; int /*<<< orphan*/  be_device; } ;
struct TYPE_2__ {size_t count; size_t offset; } ;
struct nfs_pgio_header {TYPE_1__ args; int /*<<< orphan*/  lseg; } ;
typedef  size_t sector_t ;

/* Variables and functions */
 struct pnfs_block_layout* BLK_LSEG2EXT (int /*<<< orphan*/ ) ; 
 size_t SECTOR_SHIFT ; 
 int /*<<< orphan*/  ext_tree_lookup (struct pnfs_block_layout*,size_t,struct pnfs_block_extent*,int) ; 
 int /*<<< orphan*/  nfs4_mark_deviceid_unavailable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bl_mark_devices_unavailable(struct nfs_pgio_header *header, bool rw)
{
	struct pnfs_block_layout *bl = BLK_LSEG2EXT(header->lseg);
	size_t bytes_left = header->args.count;
	sector_t isect, extent_length = 0;
	struct pnfs_block_extent be;

	isect = header->args.offset >> SECTOR_SHIFT;
	bytes_left += header->args.offset - (isect << SECTOR_SHIFT);

	while (bytes_left > 0) {
		if (!ext_tree_lookup(bl, isect, &be, rw))
				return;
		extent_length = be.be_length - (isect - be.be_f_offset);
		nfs4_mark_deviceid_unavailable(be.be_device);
		isect += extent_length;
		if (bytes_left > extent_length << SECTOR_SHIFT)
			bytes_left -= extent_length << SECTOR_SHIFT;
		else
			bytes_left = 0;
	}
}