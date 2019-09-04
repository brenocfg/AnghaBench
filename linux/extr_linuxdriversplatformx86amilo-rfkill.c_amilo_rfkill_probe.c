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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct dmi_system_id {int /*<<< orphan*/  driver_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  KBUILD_MODNAME ; 
 int /*<<< orphan*/  RFKILL_TYPE_WLAN ; 
 int /*<<< orphan*/  amilo_rfkill_dev ; 
 int /*<<< orphan*/  amilo_rfkill_id_table ; 
 struct dmi_system_id* dmi_first_match (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rfkill_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rfkill_destroy (int /*<<< orphan*/ ) ; 
 int rfkill_register (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int amilo_rfkill_probe(struct platform_device *device)
{
	int rc;
	const struct dmi_system_id *system_id =
		dmi_first_match(amilo_rfkill_id_table);

	if (!system_id)
		return -ENXIO;

	amilo_rfkill_dev = rfkill_alloc(KBUILD_MODNAME, &device->dev,
					RFKILL_TYPE_WLAN,
					system_id->driver_data, NULL);
	if (!amilo_rfkill_dev)
		return -ENOMEM;

	rc = rfkill_register(amilo_rfkill_dev);
	if (rc)
		goto fail;

	return 0;

fail:
	rfkill_destroy(amilo_rfkill_dev);
	return rc;
}