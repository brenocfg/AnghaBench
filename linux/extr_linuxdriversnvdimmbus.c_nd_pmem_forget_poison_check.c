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
struct nd_pfn {struct nd_namespace_common* ndns; } ;
struct TYPE_4__ {scalar_t__ start; scalar_t__ end; } ;
struct nd_namespace_io {TYPE_2__ res; } ;
struct nd_namespace_common {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {struct nd_namespace_common* ndns; } ;
struct nd_dax {TYPE_1__ nd_pfn; } ;
struct nd_cmd_clear_error {scalar_t__ address; scalar_t__ cleared; } ;
struct nd_btt {struct nd_namespace_common* ndns; } ;
struct device {int /*<<< orphan*/  driver; } ;
typedef  scalar_t__ resource_size_t ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ is_nd_btt (struct device*) ; 
 scalar_t__ is_nd_dax (struct device*) ; 
 scalar_t__ is_nd_pfn (struct device*) ; 
 struct nd_btt* to_nd_btt (struct device*) ; 
 struct nd_dax* to_nd_dax (struct device*) ; 
 struct nd_namespace_io* to_nd_namespace_io (int /*<<< orphan*/ *) ; 
 struct nd_pfn* to_nd_pfn (struct device*) ; 
 struct nd_namespace_common* to_ndns (struct device*) ; 

__attribute__((used)) static int nd_pmem_forget_poison_check(struct device *dev, void *data)
{
	struct nd_cmd_clear_error *clear_err =
		(struct nd_cmd_clear_error *)data;
	struct nd_btt *nd_btt = is_nd_btt(dev) ? to_nd_btt(dev) : NULL;
	struct nd_pfn *nd_pfn = is_nd_pfn(dev) ? to_nd_pfn(dev) : NULL;
	struct nd_dax *nd_dax = is_nd_dax(dev) ? to_nd_dax(dev) : NULL;
	struct nd_namespace_common *ndns = NULL;
	struct nd_namespace_io *nsio;
	resource_size_t offset = 0, end_trunc = 0, start, end, pstart, pend;

	if (nd_dax || !dev->driver)
		return 0;

	start = clear_err->address;
	end = clear_err->address + clear_err->cleared - 1;

	if (nd_btt || nd_pfn || nd_dax) {
		if (nd_btt)
			ndns = nd_btt->ndns;
		else if (nd_pfn)
			ndns = nd_pfn->ndns;
		else if (nd_dax)
			ndns = nd_dax->nd_pfn.ndns;

		if (!ndns)
			return 0;
	} else
		ndns = to_ndns(dev);

	nsio = to_nd_namespace_io(&ndns->dev);
	pstart = nsio->res.start + offset;
	pend = nsio->res.end - end_trunc;

	if ((pstart >= start) && (pend <= end))
		return -EBUSY;

	return 0;

}