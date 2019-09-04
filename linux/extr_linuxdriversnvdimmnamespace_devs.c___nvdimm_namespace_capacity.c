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
struct TYPE_2__ {int /*<<< orphan*/  res; } ;
struct nd_namespace_pmem {TYPE_1__ nsio; } ;
struct nd_namespace_io {int /*<<< orphan*/  res; } ;
struct device {int dummy; } ;
struct nd_namespace_common {struct device dev; } ;
typedef  int /*<<< orphan*/  resource_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 
 scalar_t__ is_namespace_blk (struct device*) ; 
 scalar_t__ is_namespace_io (struct device*) ; 
 scalar_t__ is_namespace_pmem (struct device*) ; 
 int /*<<< orphan*/  nd_namespace_blk_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_nd_namespace_blk (struct device*) ; 
 struct nd_namespace_io* to_nd_namespace_io (struct device*) ; 
 struct nd_namespace_pmem* to_nd_namespace_pmem (struct device*) ; 

resource_size_t __nvdimm_namespace_capacity(struct nd_namespace_common *ndns)
{
	struct device *dev = &ndns->dev;

	if (is_namespace_pmem(dev)) {
		struct nd_namespace_pmem *nspm = to_nd_namespace_pmem(dev);

		return resource_size(&nspm->nsio.res);
	} else if (is_namespace_blk(dev)) {
		return nd_namespace_blk_size(to_nd_namespace_blk(dev));
	} else if (is_namespace_io(dev)) {
		struct nd_namespace_io *nsio = to_nd_namespace_io(dev);

		return resource_size(&nsio->res);
	} else
		WARN_ONCE(1, "unknown namespace type\n");
	return 0;
}