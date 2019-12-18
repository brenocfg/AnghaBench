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
typedef  int u32 ;
struct iomap {int type; int flags; scalar_t__ addr; int /*<<< orphan*/  length; int /*<<< orphan*/  offset; } ;
struct fiemap_extent_info {int dummy; } ;

/* Variables and functions */
 int FIEMAP_EXTENT_DATA_INLINE ; 
 int FIEMAP_EXTENT_DELALLOC ; 
 int FIEMAP_EXTENT_MERGED ; 
 int FIEMAP_EXTENT_SHARED ; 
 int FIEMAP_EXTENT_UNKNOWN ; 
 int FIEMAP_EXTENT_UNWRITTEN ; 
#define  IOMAP_DELALLOC 132 
 int IOMAP_F_MERGED ; 
 int IOMAP_F_SHARED ; 
#define  IOMAP_HOLE 131 
#define  IOMAP_INLINE 130 
#define  IOMAP_MAPPED 129 
 scalar_t__ IOMAP_NULL_ADDR ; 
#define  IOMAP_UNWRITTEN 128 
 int fiemap_fill_next_extent (struct fiemap_extent_info*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int iomap_to_fiemap(struct fiemap_extent_info *fi,
		struct iomap *iomap, u32 flags)
{
	switch (iomap->type) {
	case IOMAP_HOLE:
		/* skip holes */
		return 0;
	case IOMAP_DELALLOC:
		flags |= FIEMAP_EXTENT_DELALLOC | FIEMAP_EXTENT_UNKNOWN;
		break;
	case IOMAP_MAPPED:
		break;
	case IOMAP_UNWRITTEN:
		flags |= FIEMAP_EXTENT_UNWRITTEN;
		break;
	case IOMAP_INLINE:
		flags |= FIEMAP_EXTENT_DATA_INLINE;
		break;
	}

	if (iomap->flags & IOMAP_F_MERGED)
		flags |= FIEMAP_EXTENT_MERGED;
	if (iomap->flags & IOMAP_F_SHARED)
		flags |= FIEMAP_EXTENT_SHARED;

	return fiemap_fill_next_extent(fi, iomap->offset,
			iomap->addr != IOMAP_NULL_ADDR ? iomap->addr : 0,
			iomap->length, flags);
}