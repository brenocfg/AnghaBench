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
struct hdac_hdmi_port {int id; int /*<<< orphan*/  dapm_work; struct hdac_hdmi_pin* pin; } ;
struct hdac_hdmi_pin {int num_ports; struct hdac_hdmi_port* ports; } ;
struct hdac_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HDA_MAX_PORTS ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct hdac_hdmi_port* devm_kcalloc (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdac_hdmi_jack_dapm_work ; 

__attribute__((used)) static int hdac_hdmi_add_ports(struct hdac_device *hdev,
			       struct hdac_hdmi_pin *pin)
{
	struct hdac_hdmi_port *ports;
	int max_ports = HDA_MAX_PORTS;
	int i;

	/*
	 * FIXME: max_port may vary for each platform, so pass this as
	 * as driver data or query from i915 interface when this API is
	 * implemented.
	 */

	ports = devm_kcalloc(&hdev->dev, max_ports, sizeof(*ports), GFP_KERNEL);
	if (!ports)
		return -ENOMEM;

	for (i = 0; i < max_ports; i++) {
		ports[i].id = i;
		ports[i].pin = pin;
		INIT_WORK(&ports[i].dapm_work, hdac_hdmi_jack_dapm_work);
	}
	pin->ports = ports;
	pin->num_ports = max_ports;
	return 0;
}