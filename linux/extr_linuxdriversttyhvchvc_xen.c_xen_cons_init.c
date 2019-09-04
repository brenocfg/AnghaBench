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
struct hv_ops {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HVC_COOKIE ; 
 struct hv_ops dom0_hvc_ops ; 
 struct hv_ops domU_hvc_ops ; 
 int /*<<< orphan*/  hvc_instantiate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct hv_ops const*) ; 
 int /*<<< orphan*/  xen_domain () ; 
 int xen_hvm_console_init () ; 
 scalar_t__ xen_hvm_domain () ; 
 scalar_t__ xen_initial_domain () ; 
 int xen_pv_console_init () ; 

__attribute__((used)) static int xen_cons_init(void)
{
	const struct hv_ops *ops;

	if (!xen_domain())
		return 0;

	if (xen_initial_domain())
		ops = &dom0_hvc_ops;
	else {
		int r;
		ops = &domU_hvc_ops;

		if (xen_hvm_domain())
			r = xen_hvm_console_init();
		else
			r = xen_pv_console_init();
		if (r < 0)
			return r;
	}

	hvc_instantiate(HVC_COOKIE, 0, ops);
	return 0;
}