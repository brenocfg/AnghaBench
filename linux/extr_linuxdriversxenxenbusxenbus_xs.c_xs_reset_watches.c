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

/* Variables and functions */
 int EEXIST ; 
 int /*<<< orphan*/  XBT_NIL ; 
 int /*<<< orphan*/  XS_RESET_WATCHES ; 
 int /*<<< orphan*/  pr_warn (char*,int) ; 
 int /*<<< orphan*/  xen_hvm_domain () ; 
 scalar_t__ xen_initial_domain () ; 
 scalar_t__ xen_strict_xenbus_quirk () ; 
 int /*<<< orphan*/  xenbus_read_unsigned (char*,char*,int /*<<< orphan*/ ) ; 
 int xs_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xs_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void xs_reset_watches(void)
{
	int err;

	if (!xen_hvm_domain() || xen_initial_domain())
		return;

	if (xen_strict_xenbus_quirk())
		return;

	if (!xenbus_read_unsigned("control",
				  "platform-feature-xs_reset_watches", 0))
		return;

	err = xs_error(xs_single(XBT_NIL, XS_RESET_WATCHES, "", NULL));
	if (err && err != -EEXIST)
		pr_warn("xs_reset_watches failed: %d\n", err);
}