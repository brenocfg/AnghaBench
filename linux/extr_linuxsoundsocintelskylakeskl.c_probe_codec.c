#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct skl {TYPE_1__* pci; } ;
struct hdac_device {int dummy; } ;
struct hdac_bus {int /*<<< orphan*/  dev; int /*<<< orphan*/  cmd_mutex; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int AC_NODE_ROOT ; 
 int AC_PAR_VENDOR_ID ; 
 int AC_VERB_PARAMETERS ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct skl* bus_to_skl (struct hdac_bus*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 struct hdac_device* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_hdac_bus_get_response (struct hdac_bus*,int,unsigned int*) ; 
 int /*<<< orphan*/  snd_hdac_bus_send_cmd (struct hdac_bus*,unsigned int) ; 
 int snd_hdac_ext_bus_device_init (struct hdac_bus*,int,struct hdac_device*) ; 

__attribute__((used)) static int probe_codec(struct hdac_bus *bus, int addr)
{
	unsigned int cmd = (addr << 28) | (AC_NODE_ROOT << 20) |
		(AC_VERB_PARAMETERS << 8) | AC_PAR_VENDOR_ID;
	unsigned int res = -1;
	struct skl *skl = bus_to_skl(bus);
	struct hdac_device *hdev;

	mutex_lock(&bus->cmd_mutex);
	snd_hdac_bus_send_cmd(bus, cmd);
	snd_hdac_bus_get_response(bus, addr, &res);
	mutex_unlock(&bus->cmd_mutex);
	if (res == -1)
		return -EIO;
	dev_dbg(bus->dev, "codec #%d probed OK\n", addr);

	hdev = devm_kzalloc(&skl->pci->dev, sizeof(*hdev), GFP_KERNEL);
	if (!hdev)
		return -ENOMEM;

	return snd_hdac_ext_bus_device_init(bus, addr, hdev);
}