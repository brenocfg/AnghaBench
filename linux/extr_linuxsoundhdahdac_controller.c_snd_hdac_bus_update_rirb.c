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
typedef  int u32 ;
struct TYPE_2__ {unsigned int wp; unsigned int rp; int* res; scalar_t__* cmds; int /*<<< orphan*/ * buf; } ;
struct hdac_bus {int /*<<< orphan*/ * last_cmd; int /*<<< orphan*/  dev; TYPE_1__ rirb; } ;

/* Variables and functions */
 unsigned int AZX_MAX_RIRB_ENTRIES ; 
 int AZX_RIRB_EX_UNSOL_EV ; 
 unsigned int HDA_MAX_CODECS ; 
 int /*<<< orphan*/  RIRBWP ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int,int,unsigned int) ; 
 int /*<<< orphan*/  dev_err_ratelimited (int /*<<< orphan*/ ,char*,int,int,int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_BUG () ; 
 int /*<<< orphan*/  snd_hdac_bus_queue_event (struct hdac_bus*,int,int) ; 
 unsigned int snd_hdac_chip_readw (struct hdac_bus*,int /*<<< orphan*/ ) ; 

void snd_hdac_bus_update_rirb(struct hdac_bus *bus)
{
	unsigned int rp, wp;
	unsigned int addr;
	u32 res, res_ex;

	wp = snd_hdac_chip_readw(bus, RIRBWP);
	if (wp == 0xffff) {
		/* something wrong, controller likely turned to D3 */
		return;
	}

	if (wp == bus->rirb.wp)
		return;
	bus->rirb.wp = wp;

	while (bus->rirb.rp != wp) {
		bus->rirb.rp++;
		bus->rirb.rp %= AZX_MAX_RIRB_ENTRIES;

		rp = bus->rirb.rp << 1; /* an RIRB entry is 8-bytes */
		res_ex = le32_to_cpu(bus->rirb.buf[rp + 1]);
		res = le32_to_cpu(bus->rirb.buf[rp]);
		addr = res_ex & 0xf;
		if (addr >= HDA_MAX_CODECS) {
			dev_err(bus->dev,
				"spurious response %#x:%#x, rp = %d, wp = %d",
				res, res_ex, bus->rirb.rp, wp);
			snd_BUG();
		} else if (res_ex & AZX_RIRB_EX_UNSOL_EV)
			snd_hdac_bus_queue_event(bus, res, res_ex);
		else if (bus->rirb.cmds[addr]) {
			bus->rirb.res[addr] = res;
			bus->rirb.cmds[addr]--;
		} else {
			dev_err_ratelimited(bus->dev,
				"spurious response %#x:%#x, last cmd=%#08x\n",
				res, res_ex, bus->last_cmd[addr]);
		}
	}
}