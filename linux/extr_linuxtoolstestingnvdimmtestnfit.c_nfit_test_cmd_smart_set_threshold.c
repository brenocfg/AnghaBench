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
struct nd_intel_smart_threshold {int /*<<< orphan*/  data; } ;
struct nd_intel_smart_set_threshold {scalar_t__ status; } ;
struct nd_intel_smart {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,struct nd_intel_smart_set_threshold*,unsigned int) ; 
 int /*<<< orphan*/  smart_notify (struct device*,struct device*,struct nd_intel_smart*,struct nd_intel_smart_threshold*) ; 

__attribute__((used)) static int nfit_test_cmd_smart_set_threshold(
		struct nd_intel_smart_set_threshold *in,
		unsigned int buf_len,
		struct nd_intel_smart_threshold *thresh,
		struct nd_intel_smart *smart,
		struct device *bus_dev, struct device *dimm_dev)
{
	unsigned int size;

	size = sizeof(*in) - 4;
	if (buf_len < size)
		return -EINVAL;
	memcpy(thresh->data, in, size);
	in->status = 0;
	smart_notify(bus_dev, dimm_dev, smart, thresh);

	return 0;
}