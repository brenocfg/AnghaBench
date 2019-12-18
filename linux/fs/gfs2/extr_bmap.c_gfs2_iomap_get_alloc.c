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
struct metapath {int mp_aheight; } ;
struct iomap {scalar_t__ type; } ;
struct inode {int dummy; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 scalar_t__ IOMAP_HOLE ; 
 int /*<<< orphan*/  IOMAP_WRITE ; 
 int gfs2_iomap_alloc (struct inode*,struct iomap*,struct metapath*) ; 
 int gfs2_iomap_get (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct iomap*,struct metapath*) ; 
 int /*<<< orphan*/  release_metapath (struct metapath*) ; 

int gfs2_iomap_get_alloc(struct inode *inode, loff_t pos, loff_t length,
			 struct iomap *iomap)
{
	struct metapath mp = { .mp_aheight = 1, };
	int ret;

	ret = gfs2_iomap_get(inode, pos, length, IOMAP_WRITE, iomap, &mp);
	if (!ret && iomap->type == IOMAP_HOLE)
		ret = gfs2_iomap_alloc(inode, iomap, &mp);
	release_metapath(&mp);
	return ret;
}