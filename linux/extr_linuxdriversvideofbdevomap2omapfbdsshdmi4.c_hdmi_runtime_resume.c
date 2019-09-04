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
struct device {int dummy; } ;

/* Variables and functions */
 int dispc_runtime_get () ; 

__attribute__((used)) static int hdmi_runtime_resume(struct device *dev)
{
	int r;

	r = dispc_runtime_get();
	if (r < 0)
		return r;

	return 0;
}