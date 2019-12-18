#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ length; scalar_t__ addr; } ;
struct iomap_swapfile_info {TYPE_2__ iomap; TYPE_1__* sis; } ;
struct iomap {int type; int flags; scalar_t__ bdev; scalar_t__ addr; scalar_t__ length; } ;
struct inode {int dummy; } ;
typedef  int loff_t ;
struct TYPE_3__ {scalar_t__ bdev; } ;

/* Variables and functions */
 int EINVAL ; 
 int IOMAP_F_DIRTY ; 
 int IOMAP_F_SHARED ; 
#define  IOMAP_INLINE 130 
#define  IOMAP_MAPPED 129 
#define  IOMAP_UNWRITTEN 128 
 int iomap_swapfile_add_extent (struct iomap_swapfile_info*) ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,struct iomap*,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static loff_t iomap_swapfile_activate_actor(struct inode *inode, loff_t pos,
		loff_t count, void *data, struct iomap *iomap)
{
	struct iomap_swapfile_info *isi = data;
	int error;

	switch (iomap->type) {
	case IOMAP_MAPPED:
	case IOMAP_UNWRITTEN:
		/* Only real or unwritten extents. */
		break;
	case IOMAP_INLINE:
		/* No inline data. */
		pr_err("swapon: file is inline\n");
		return -EINVAL;
	default:
		pr_err("swapon: file has unallocated extents\n");
		return -EINVAL;
	}

	/* No uncommitted metadata or shared blocks. */
	if (iomap->flags & IOMAP_F_DIRTY) {
		pr_err("swapon: file is not committed\n");
		return -EINVAL;
	}
	if (iomap->flags & IOMAP_F_SHARED) {
		pr_err("swapon: file has shared extents\n");
		return -EINVAL;
	}

	/* Only one bdev per swap file. */
	if (iomap->bdev != isi->sis->bdev) {
		pr_err("swapon: file is on multiple devices\n");
		return -EINVAL;
	}

	if (isi->iomap.length == 0) {
		/* No accumulated extent, so just store it. */
		memcpy(&isi->iomap, iomap, sizeof(isi->iomap));
	} else if (isi->iomap.addr + isi->iomap.length == iomap->addr) {
		/* Append this to the accumulated extent. */
		isi->iomap.length += iomap->length;
	} else {
		/* Otherwise, add the retained iomap and store this one. */
		error = iomap_swapfile_add_extent(isi);
		if (error)
			return error;
		memcpy(&isi->iomap, iomap, sizeof(isi->iomap));
	}
	return count;
}