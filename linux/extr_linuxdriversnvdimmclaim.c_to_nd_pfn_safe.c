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
struct nd_pfn {int dummy; } ;
struct nd_dax {struct nd_pfn nd_pfn; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ is_nd_dax (struct device*) ; 
 scalar_t__ is_nd_pfn (struct device*) ; 
 struct nd_dax* to_nd_dax (struct device*) ; 
 struct nd_pfn* to_nd_pfn (struct device*) ; 

struct nd_pfn *to_nd_pfn_safe(struct device *dev)
{
	/*
	 * pfn device attributes are re-used by dax device instances, so we
	 * need to be careful to correct device-to-nd_pfn conversion.
	 */
	if (is_nd_pfn(dev))
		return to_nd_pfn(dev);

	if (is_nd_dax(dev)) {
		struct nd_dax *nd_dax = to_nd_dax(dev);

		return &nd_dax->nd_pfn;
	}

	WARN_ON(1);
	return NULL;
}