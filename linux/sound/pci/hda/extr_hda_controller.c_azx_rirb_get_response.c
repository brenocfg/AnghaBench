#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned int* res; int /*<<< orphan*/ * cmds; } ;
struct hdac_bus {int polling_mode; int poll_count; int /*<<< orphan*/ * last_cmd; int /*<<< orphan*/  reg_lock; TYPE_1__ rirb; } ;
struct hda_bus {int response_reset; int /*<<< orphan*/  in_reset; scalar_t__ allow_bus_reset; scalar_t__ no_response_fallback; scalar_t__ needs_damn_long_delay; } ;
struct azx {int single_cmd; TYPE_3__* card; int /*<<< orphan*/  fallback_to_single_cmd; scalar_t__ probing; TYPE_2__* ops; scalar_t__ msi; struct hda_bus bus; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {scalar_t__ (* disable_msi_reset_irq ) (struct azx*) ;} ;

/* Variables and functions */
 int EAGAIN ; 
 int EIO ; 
 unsigned long LOOP_COUNT_MAX ; 
 struct azx* bus_to_azx (struct hdac_bus*) ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  dev_WARN (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg_ratelimited (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  snd_hdac_bus_stop_cmd_io (struct hdac_bus*) ; 
 int /*<<< orphan*/  snd_hdac_bus_update_rirb (struct hdac_bus*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (struct azx*) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int azx_rirb_get_response(struct hdac_bus *bus, unsigned int addr,
				 unsigned int *res)
{
	struct azx *chip = bus_to_azx(bus);
	struct hda_bus *hbus = &chip->bus;
	unsigned long timeout;
	unsigned long loopcounter;
	int do_poll = 0;
	bool warned = false;

 again:
	timeout = jiffies + msecs_to_jiffies(1000);

	for (loopcounter = 0;; loopcounter++) {
		spin_lock_irq(&bus->reg_lock);
		if (bus->polling_mode || do_poll)
			snd_hdac_bus_update_rirb(bus);
		if (!bus->rirb.cmds[addr]) {
			if (!do_poll)
				bus->poll_count = 0;
			if (res)
				*res = bus->rirb.res[addr]; /* the last value */
			spin_unlock_irq(&bus->reg_lock);
			return 0;
		}
		spin_unlock_irq(&bus->reg_lock);
		if (time_after(jiffies, timeout))
			break;
#define LOOP_COUNT_MAX	3000
		if (hbus->needs_damn_long_delay ||
		    loopcounter > LOOP_COUNT_MAX) {
			if (loopcounter > LOOP_COUNT_MAX && !warned) {
				dev_dbg_ratelimited(chip->card->dev,
						    "too slow response, last cmd=%#08x\n",
						    bus->last_cmd[addr]);
				warned = true;
			}
			msleep(2); /* temporary workaround */
		} else {
			udelay(10);
			cond_resched();
		}
	}

	if (hbus->no_response_fallback)
		return -EIO;

	if (!bus->polling_mode && bus->poll_count < 2) {
		dev_dbg(chip->card->dev,
			"azx_get_response timeout, polling the codec once: last cmd=0x%08x\n",
			bus->last_cmd[addr]);
		do_poll = 1;
		bus->poll_count++;
		goto again;
	}


	if (!bus->polling_mode) {
		dev_warn(chip->card->dev,
			 "azx_get_response timeout, switching to polling mode: last cmd=0x%08x\n",
			 bus->last_cmd[addr]);
		bus->polling_mode = 1;
		goto again;
	}

	if (chip->msi) {
		dev_warn(chip->card->dev,
			 "No response from codec, disabling MSI: last cmd=0x%08x\n",
			 bus->last_cmd[addr]);
		if (chip->ops->disable_msi_reset_irq &&
		    chip->ops->disable_msi_reset_irq(chip) < 0)
			return -EIO;
		goto again;
	}

	if (chip->probing) {
		/* If this critical timeout happens during the codec probing
		 * phase, this is likely an access to a non-existing codec
		 * slot.  Better to return an error and reset the system.
		 */
		return -EIO;
	}

	/* no fallback mechanism? */
	if (!chip->fallback_to_single_cmd)
		return -EIO;

	/* a fatal communication error; need either to reset or to fallback
	 * to the single_cmd mode
	 */
	if (hbus->allow_bus_reset && !hbus->response_reset && !hbus->in_reset) {
		hbus->response_reset = 1;
		dev_err(chip->card->dev,
			"No response from codec, resetting bus: last cmd=0x%08x\n",
			bus->last_cmd[addr]);
		return -EAGAIN; /* give a chance to retry */
	}

	dev_WARN(chip->card->dev,
		"azx_get_response timeout, switching to single_cmd mode: last cmd=0x%08x\n",
		bus->last_cmd[addr]);
	chip->single_cmd = 1;
	hbus->response_reset = 0;
	snd_hdac_bus_stop_cmd_io(bus);
	return -EIO;
}