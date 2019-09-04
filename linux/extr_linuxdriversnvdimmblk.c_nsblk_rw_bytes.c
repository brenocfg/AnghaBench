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
struct nd_namespace_common {int /*<<< orphan*/  dev; } ;
struct nd_namespace_blk {scalar_t__ size; } ;
struct nd_blk_region {int (* do_io ) (struct nd_blk_region*,scalar_t__,void*,size_t,int) ;} ;
typedef  scalar_t__ resource_size_t ;

/* Variables and functions */
 int EFAULT ; 
 int EIO ; 
 scalar_t__ SIZE_MAX ; 
 int /*<<< orphan*/  dev_WARN_ONCE (int /*<<< orphan*/ *,int,char*) ; 
 int stub1 (struct nd_blk_region*,scalar_t__,void*,size_t,int) ; 
 scalar_t__ to_dev_offset (struct nd_namespace_blk*,scalar_t__,size_t) ; 
 struct nd_namespace_blk* to_nd_namespace_blk (int /*<<< orphan*/ *) ; 
 struct nd_blk_region* to_ndbr (struct nd_namespace_blk*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int nsblk_rw_bytes(struct nd_namespace_common *ndns,
		resource_size_t offset, void *iobuf, size_t n, int rw,
		unsigned long flags)
{
	struct nd_namespace_blk *nsblk = to_nd_namespace_blk(&ndns->dev);
	struct nd_blk_region *ndbr = to_ndbr(nsblk);
	resource_size_t	dev_offset;

	dev_offset = to_dev_offset(nsblk, offset, n);

	if (unlikely(offset + n > nsblk->size)) {
		dev_WARN_ONCE(&ndns->dev, 1, "request out of range\n");
		return -EFAULT;
	}

	if (dev_offset == SIZE_MAX)
		return -EIO;

	return ndbr->do_io(ndbr, dev_offset, iobuf, n, rw);
}