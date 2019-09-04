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
struct hdac_hdmi_priv {int dummy; } ;
struct hdac_hdmi_port {int id; struct hdac_hdmi_pin* pin; } ;
struct hdac_hdmi_pin {int num_ports; struct hdac_hdmi_port* ports; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HDA_MAX_PORTS ; 
 struct hdac_hdmi_port* kcalloc (int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hdac_hdmi_add_ports(struct hdac_hdmi_priv *hdmi,
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

	ports = kcalloc(max_ports, sizeof(*ports), GFP_KERNEL);
	if (!ports)
		return -ENOMEM;

	for (i = 0; i < max_ports; i++) {
		ports[i].id = i;
		ports[i].pin = pin;
	}
	pin->ports = ports;
	pin->num_ports = max_ports;
	return 0;
}