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
struct pnp_dev {int dummy; } ;
struct apple_gmux_data {scalar_t__ gpe; int /*<<< orphan*/  iolen; int /*<<< orphan*/  iostart; int /*<<< orphan*/  bdev; int /*<<< orphan*/  dhandle; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DEVICE_NOTIFY ; 
 int /*<<< orphan*/  acpi_disable_gpe (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  acpi_remove_notify_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_video_register () ; 
 int /*<<< orphan*/  apple_bl_register () ; 
 int /*<<< orphan*/ * apple_gmux_data ; 
 int /*<<< orphan*/  backlight_device_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gmux_disable_interrupts (struct apple_gmux_data*) ; 
 int /*<<< orphan*/  gmux_notify_handler ; 
 int /*<<< orphan*/  kfree (struct apple_gmux_data*) ; 
 struct apple_gmux_data* pnp_get_drvdata (struct pnp_dev*) ; 
 int /*<<< orphan*/  release_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vga_switcheroo_unregister_handler () ; 

__attribute__((used)) static void gmux_remove(struct pnp_dev *pnp)
{
	struct apple_gmux_data *gmux_data = pnp_get_drvdata(pnp);

	vga_switcheroo_unregister_handler();
	gmux_disable_interrupts(gmux_data);
	if (gmux_data->gpe >= 0) {
		acpi_disable_gpe(NULL, gmux_data->gpe);
		acpi_remove_notify_handler(gmux_data->dhandle,
					   ACPI_DEVICE_NOTIFY,
					   &gmux_notify_handler);
	}

	backlight_device_unregister(gmux_data->bdev);

	release_region(gmux_data->iostart, gmux_data->iolen);
	apple_gmux_data = NULL;
	kfree(gmux_data);

	acpi_video_register();
	apple_bl_register();
}