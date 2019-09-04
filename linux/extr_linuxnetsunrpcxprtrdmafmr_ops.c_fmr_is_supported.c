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
struct rpcrdma_ia {TYPE_1__* ri_device; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; int /*<<< orphan*/  alloc_fmr; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 

bool
fmr_is_supported(struct rpcrdma_ia *ia)
{
	if (!ia->ri_device->alloc_fmr) {
		pr_info("rpcrdma: 'fmr' mode is not supported by device %s\n",
			ia->ri_device->name);
		return false;
	}
	return true;
}