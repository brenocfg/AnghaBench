#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct rpi_axiperf {int dummy; } ;
struct resource {int dummy; } ;
struct device {struct device_node* of_node; } ;
struct platform_device {struct device dev; } ;
struct device_node {int dummy; } ;
struct TYPE_7__ {int sample_time; int /*<<< orphan*/  monitor_thread; int /*<<< orphan*/  lock; TYPE_1__* monitor; int /*<<< orphan*/ * root_folder; struct platform_device* dev; int /*<<< orphan*/  firmware; } ;
struct TYPE_6__ {int use_mailbox_interface; int bus_enabled; int bus_filter; int /*<<< orphan*/ * debugfs_entry; int /*<<< orphan*/ * base_address; } ;

/* Variables and functions */
 int DEFAULT_SAMPLE_TIME ; 
 int ENOENT ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KBUILD_MODNAME ; 
 int NUM_MONITORS ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 size_t SYSTEM_MONITOR ; 
 size_t VPU_MONITOR ; 
 void* debugfs_create_dir (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_u32 (char*,int,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/ * devm_ioremap_resource (struct device*,struct resource*) ; 
 int /*<<< orphan*/  fops_debug ; 
 int /*<<< orphan*/  kthread_run (int /*<<< orphan*/ ,TYPE_2__*,char*) ; 
 TYPE_2__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * monitor_name ; 
 int /*<<< orphan*/  monitor_thread ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct device_node* of_parse_phandle (struct device_node*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_property_read_u32_index (struct device_node*,char*,int,int /*<<< orphan*/ *) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,TYPE_2__*) ; 
 int /*<<< orphan*/  rpi_firmware_get (struct device_node*) ; 
 TYPE_2__* state ; 

__attribute__((used)) static int rpi_axiperf_probe(struct platform_device *pdev)
{
	int ret = 0, i;
	struct device *dev = &pdev->dev;
	struct device_node *np = dev->of_node;
	struct device_node *fw_node;

	state = kzalloc(sizeof(struct rpi_axiperf), GFP_KERNEL);
	if (!state)
		return -ENOMEM;

	/* Get the firmware handle for future rpi-firmware-xxx calls */
	fw_node = of_parse_phandle(np, "firmware", 0);
	if (!fw_node) {
		dev_err(dev, "Missing firmware node\n");
		return -ENOENT;
	}

	state->firmware = rpi_firmware_get(fw_node);
	if (!state->firmware)
		return -EPROBE_DEFER;

	/* Special case for the VPU monitor, we must use the mailbox interface
	 * as it is not accessible from the ARM address space.
	 */
	state->monitor[VPU_MONITOR].use_mailbox_interface = 1;
	state->monitor[SYSTEM_MONITOR].use_mailbox_interface = 0;

	for (i = 0; i < NUM_MONITORS; i++) {
		if (state->monitor[i].use_mailbox_interface) {
			 of_property_read_u32_index(np, "reg", i*2,
				(u32 *)(&state->monitor[i].base_address));
		} else {
			struct resource *resource =
				platform_get_resource(pdev, IORESOURCE_MEM, i);

			state->monitor[i].base_address =
				devm_ioremap_resource(&pdev->dev, resource);
		}

		if (IS_ERR(state->monitor[i].base_address))
			return PTR_ERR(state->monitor[i].base_address);

		/* Enable all buses by default */
		state->monitor[i].bus_enabled = 0xffff;
	}

	state->dev = pdev;
	platform_set_drvdata(pdev, state);

	state->sample_time = DEFAULT_SAMPLE_TIME;

	/* Set up all the debugfs stuff */
	state->root_folder = debugfs_create_dir(KBUILD_MODNAME, NULL);

	for (i = 0; i < NUM_MONITORS; i++) {
		state->monitor[i].debugfs_entry =
			debugfs_create_dir(monitor_name[i], state->root_folder);
		if (IS_ERR(state->monitor[i].debugfs_entry))
			state->monitor[i].debugfs_entry = NULL;

		debugfs_create_file("data", 0444,
				    state->monitor[i].debugfs_entry,
				    (void *)i, &fops_debug);
		debugfs_create_u32("enable", 0644,
				   state->monitor[i].debugfs_entry,
				   &state->monitor[i].bus_enabled);
		debugfs_create_u32("filter", 0644,
				   state->monitor[i].debugfs_entry,
				   &state->monitor[i].bus_filter);
		debugfs_create_u32("sample_time", 0644,
				   state->monitor[i].debugfs_entry,
				   &state->sample_time);
	}

	mutex_init(&state->lock);

	state->monitor_thread = kthread_run(monitor_thread, state,
					    "rpi-axiperfmon");

	return ret;

}