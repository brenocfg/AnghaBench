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
struct iomap {int type; } ;
struct inode {int dummy; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
#define  IOMAP_HOLE 129 
#define  IOMAP_UNWRITTEN 128 
 int /*<<< orphan*/  SEEK_DATA ; 
 int /*<<< orphan*/  page_cache_seek_hole_data (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static loff_t
iomap_seek_data_actor(struct inode *inode, loff_t offset, loff_t length,
		      void *data, struct iomap *iomap)
{
	switch (iomap->type) {
	case IOMAP_HOLE:
		return length;
	case IOMAP_UNWRITTEN:
		offset = page_cache_seek_hole_data(inode, offset, length,
						   SEEK_DATA);
		if (offset < 0)
			return length;
		/*FALLTHRU*/
	default:
		*(loff_t *)data = offset;
		return 0;
	}
}