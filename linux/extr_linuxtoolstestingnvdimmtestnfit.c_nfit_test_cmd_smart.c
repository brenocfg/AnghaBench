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
struct nd_intel_smart {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  memcpy (struct nd_intel_smart*,struct nd_intel_smart*,int) ; 

__attribute__((used)) static int nfit_test_cmd_smart(struct nd_intel_smart *smart, unsigned int buf_len,
		struct nd_intel_smart *smart_data)
{
	if (buf_len < sizeof(*smart))
		return -EINVAL;
	memcpy(smart, smart_data, sizeof(*smart));
	return 0;
}