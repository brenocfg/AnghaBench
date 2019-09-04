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
struct gb_bundle {int /*<<< orphan*/  dev; int /*<<< orphan*/  links; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_del (int /*<<< orphan*/ *) ; 
 scalar_t__ device_is_registered (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_gb_bundle_destroy (struct gb_bundle*) ; 

void gb_bundle_destroy(struct gb_bundle *bundle)
{
	trace_gb_bundle_destroy(bundle);

	if (device_is_registered(&bundle->dev))
		device_del(&bundle->dev);

	list_del(&bundle->links);

	put_device(&bundle->dev);
}