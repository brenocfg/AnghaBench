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
struct hdac_bus {int /*<<< orphan*/  cmd_mutex; } ;
struct azx {int probing; TYPE_1__* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int AC_NODE_ROOT ; 
 int AC_PAR_VENDOR_ID ; 
 int AC_VERB_PARAMETERS ; 
 int EIO ; 
 struct hdac_bus* azx_bus (struct azx*) ; 
 int azx_get_response (struct hdac_bus*,int,unsigned int*) ; 
 int /*<<< orphan*/  azx_send_cmd (struct hdac_bus*,unsigned int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int probe_codec(struct azx *chip, int addr)
{
	unsigned int cmd = (addr << 28) | (AC_NODE_ROOT << 20) |
		(AC_VERB_PARAMETERS << 8) | AC_PAR_VENDOR_ID;
	struct hdac_bus *bus = azx_bus(chip);
	int err;
	unsigned int res = -1;

	mutex_lock(&bus->cmd_mutex);
	chip->probing = 1;
	azx_send_cmd(bus, cmd);
	err = azx_get_response(bus, addr, &res);
	chip->probing = 0;
	mutex_unlock(&bus->cmd_mutex);
	if (err < 0 || res == -1)
		return -EIO;
	dev_dbg(chip->card->dev, "codec #%d probed OK\n", addr);
	return 0;
}