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
typedef  int u8 ;
typedef  int u32 ;
struct ssb_bus {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  SSB_BAR0_MAX_RETRIES ; 
 int SSB_CORE_SIZE ; 
 int SSB_ENUM_BASE ; 
 int /*<<< orphan*/  SSB_PCMCIA_ADDRESS0 ; 
 int /*<<< orphan*/  SSB_PCMCIA_ADDRESS1 ; 
 int /*<<< orphan*/  SSB_PCMCIA_ADDRESS2 ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int ssb_pcmcia_cfg_read (struct ssb_bus*,int /*<<< orphan*/ ,int*) ; 
 int ssb_pcmcia_cfg_write (struct ssb_bus*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

int ssb_pcmcia_switch_coreidx(struct ssb_bus *bus,
			      u8 coreidx)
{
	int err;
	int attempts = 0;
	u32 cur_core;
	u32 addr;
	u32 read_addr;
	u8 val;

	addr = (coreidx * SSB_CORE_SIZE) + SSB_ENUM_BASE;
	while (1) {
		err = ssb_pcmcia_cfg_write(bus, SSB_PCMCIA_ADDRESS0,
					   (addr & 0x0000F000) >> 12);
		if (err)
			goto error;
		err = ssb_pcmcia_cfg_write(bus, SSB_PCMCIA_ADDRESS1,
					   (addr & 0x00FF0000) >> 16);
		if (err)
			goto error;
		err = ssb_pcmcia_cfg_write(bus, SSB_PCMCIA_ADDRESS2,
					   (addr & 0xFF000000) >> 24);
		if (err)
			goto error;

		read_addr = 0;

		err = ssb_pcmcia_cfg_read(bus, SSB_PCMCIA_ADDRESS0, &val);
		if (err)
			goto error;
		read_addr |= ((u32)(val & 0x0F)) << 12;
		err = ssb_pcmcia_cfg_read(bus, SSB_PCMCIA_ADDRESS1, &val);
		if (err)
			goto error;
		read_addr |= ((u32)val) << 16;
		err = ssb_pcmcia_cfg_read(bus, SSB_PCMCIA_ADDRESS2, &val);
		if (err)
			goto error;
		read_addr |= ((u32)val) << 24;

		cur_core = (read_addr - SSB_ENUM_BASE) / SSB_CORE_SIZE;
		if (cur_core == coreidx)
			break;

		err = -ETIMEDOUT;
		if (attempts++ > SSB_BAR0_MAX_RETRIES)
			goto error;
		udelay(10);
	}

	return 0;
error:
	pr_err("Failed to switch to core %u\n", coreidx);
	return err;
}