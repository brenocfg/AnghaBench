#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct visorchannel {int dummy; } ;
struct visor_controlvm_channel {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  kobj; } ;
struct acpi_device {TYPE_1__ dev; TYPE_2__* driver_data; } ;
struct TYPE_8__ {struct visorchannel* controlvm_channel; struct acpi_device* acpi_device; int /*<<< orphan*/  periodic_controlvm_work; void* poll_jiffies; int /*<<< orphan*/  most_recent_message_jiffies; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* POLLJIFFIES_CONTROLVM_FAST ; 
 int /*<<< orphan*/  VISOR_CHANNEL_SIGNATURE ; 
 int /*<<< orphan*/  VISOR_CONTROLVM_CHANNEL_VERSIONID ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 TYPE_2__* chipset_dev ; 
 int controlvm_channel_create (TYPE_2__*) ; 
 int /*<<< orphan*/  controlvm_periodic_work ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,int) ; 
 scalar_t__ is_kdump_kernel () ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 
 TYPE_2__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  setup_crash_devices_work_queue ; 
 int sysfs_create_groups (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysfs_remove_groups (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  visor_check_channel (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  visor_controlvm_channel_guid ; 
 int visorbus_init () ; 
 int /*<<< orphan*/  visorchannel_destroy (struct visorchannel*) ; 
 int /*<<< orphan*/  visorchannel_get_header (struct visorchannel*) ; 
 int /*<<< orphan*/  visorchipset_dev_groups ; 

__attribute__((used)) static int visorchipset_init(struct acpi_device *acpi_device)
{
	int err = -ENODEV;
	struct visorchannel *controlvm_channel;

	chipset_dev = kzalloc(sizeof(*chipset_dev), GFP_KERNEL);
	if (!chipset_dev)
		goto error;
	err = controlvm_channel_create(chipset_dev);
	if (err)
		goto error_free_chipset_dev;
	acpi_device->driver_data = chipset_dev;
	chipset_dev->acpi_device = acpi_device;
	chipset_dev->poll_jiffies = POLLJIFFIES_CONTROLVM_FAST;
	err = sysfs_create_groups(&chipset_dev->acpi_device->dev.kobj,
				  visorchipset_dev_groups);
	if (err < 0)
		goto error_destroy_channel;
	controlvm_channel = chipset_dev->controlvm_channel;
	if (!visor_check_channel(visorchannel_get_header(controlvm_channel),
				 &chipset_dev->acpi_device->dev,
				 &visor_controlvm_channel_guid,
				 "controlvm",
				 sizeof(struct visor_controlvm_channel),
				 VISOR_CONTROLVM_CHANNEL_VERSIONID,
				 VISOR_CHANNEL_SIGNATURE))
		goto error_delete_groups;
	/* if booting in a crash kernel */
	if (is_kdump_kernel())
		INIT_DELAYED_WORK(&chipset_dev->periodic_controlvm_work,
				  setup_crash_devices_work_queue);
	else
		INIT_DELAYED_WORK(&chipset_dev->periodic_controlvm_work,
				  controlvm_periodic_work);
	chipset_dev->most_recent_message_jiffies = jiffies;
	chipset_dev->poll_jiffies = POLLJIFFIES_CONTROLVM_FAST;
	schedule_delayed_work(&chipset_dev->periodic_controlvm_work,
			      chipset_dev->poll_jiffies);
	err = visorbus_init();
	if (err < 0)
		goto error_cancel_work;
	return 0;

error_cancel_work:
	cancel_delayed_work_sync(&chipset_dev->periodic_controlvm_work);

error_delete_groups:
	sysfs_remove_groups(&chipset_dev->acpi_device->dev.kobj,
			    visorchipset_dev_groups);

error_destroy_channel:
	visorchannel_destroy(chipset_dev->controlvm_channel);

error_free_chipset_dev:
	kfree(chipset_dev);

error:
	dev_err(&acpi_device->dev, "failed with error %d\n", err);
	return err;
}