#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * buf; } ;
struct TYPE_3__ {int /*<<< orphan*/ * cmds; } ;
struct hdac_bus {unsigned int* last_cmd; int /*<<< orphan*/  reg_lock; TYPE_2__ corb; TYPE_1__ rirb; } ;

/* Variables and functions */
 unsigned int AZX_MAX_CORB_ENTRIES ; 
 int /*<<< orphan*/  CORBRP ; 
 int /*<<< orphan*/  CORBWP ; 
 int EAGAIN ; 
 int EIO ; 
 size_t azx_command_addr (unsigned int) ; 
 int /*<<< orphan*/  cpu_to_le32 (unsigned int) ; 
 unsigned int snd_hdac_chip_readw (struct hdac_bus*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hdac_chip_writew (struct hdac_bus*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

int snd_hdac_bus_send_cmd(struct hdac_bus *bus, unsigned int val)
{
	unsigned int addr = azx_command_addr(val);
	unsigned int wp, rp;

	spin_lock_irq(&bus->reg_lock);

	bus->last_cmd[azx_command_addr(val)] = val;

	/* add command to corb */
	wp = snd_hdac_chip_readw(bus, CORBWP);
	if (wp == 0xffff) {
		/* something wrong, controller likely turned to D3 */
		spin_unlock_irq(&bus->reg_lock);
		return -EIO;
	}
	wp++;
	wp %= AZX_MAX_CORB_ENTRIES;

	rp = snd_hdac_chip_readw(bus, CORBRP);
	if (wp == rp) {
		/* oops, it's full */
		spin_unlock_irq(&bus->reg_lock);
		return -EAGAIN;
	}

	bus->rirb.cmds[addr]++;
	bus->corb.buf[wp] = cpu_to_le32(val);
	snd_hdac_chip_writew(bus, CORBWP, wp);

	spin_unlock_irq(&bus->reg_lock);

	return 0;
}