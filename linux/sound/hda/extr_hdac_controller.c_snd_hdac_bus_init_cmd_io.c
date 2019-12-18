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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_6__ {scalar_t__ addr; int /*<<< orphan*/  cmds; scalar_t__ rp; scalar_t__ wp; int /*<<< orphan*/ * buf; } ;
struct TYPE_5__ {scalar_t__ area; scalar_t__ addr; } ;
struct TYPE_4__ {scalar_t__ addr; int /*<<< orphan*/ * buf; } ;
struct hdac_bus {int /*<<< orphan*/  reg_lock; TYPE_3__ rirb; TYPE_2__ rb; int /*<<< orphan*/  corbrp_self_clear; TYPE_1__ corb; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int AZX_CORBCTL_RUN ; 
 int AZX_CORBRP_RST ; 
 int /*<<< orphan*/  AZX_GCTL_UNSOL ; 
 int AZX_RBCTL_DMA_EN ; 
 int AZX_RBCTL_IRQ_EN ; 
 int AZX_RIRBWP_RST ; 
 int /*<<< orphan*/  CORBCTL ; 
 int /*<<< orphan*/  CORBLBASE ; 
 int /*<<< orphan*/  CORBRP ; 
 int /*<<< orphan*/  CORBSIZE ; 
 int /*<<< orphan*/  CORBUBASE ; 
 int /*<<< orphan*/  CORBWP ; 
 int /*<<< orphan*/  GCTL ; 
 int /*<<< orphan*/  RINTCNT ; 
 int /*<<< orphan*/  RIRBCTL ; 
 int /*<<< orphan*/  RIRBLBASE ; 
 int /*<<< orphan*/  RIRBSIZE ; 
 int /*<<< orphan*/  RIRBUBASE ; 
 int /*<<< orphan*/  RIRBWP ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  azx_clear_corbrp (struct hdac_bus*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_hdac_chip_updatel (struct hdac_bus*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hdac_chip_writeb (struct hdac_bus*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_hdac_chip_writel (struct hdac_bus*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hdac_chip_writew (struct hdac_bus*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  upper_32_bits (scalar_t__) ; 

void snd_hdac_bus_init_cmd_io(struct hdac_bus *bus)
{
	WARN_ON_ONCE(!bus->rb.area);

	spin_lock_irq(&bus->reg_lock);
	/* CORB set up */
	bus->corb.addr = bus->rb.addr;
	bus->corb.buf = (__le32 *)bus->rb.area;
	snd_hdac_chip_writel(bus, CORBLBASE, (u32)bus->corb.addr);
	snd_hdac_chip_writel(bus, CORBUBASE, upper_32_bits(bus->corb.addr));

	/* set the corb size to 256 entries (ULI requires explicitly) */
	snd_hdac_chip_writeb(bus, CORBSIZE, 0x02);
	/* set the corb write pointer to 0 */
	snd_hdac_chip_writew(bus, CORBWP, 0);

	/* reset the corb hw read pointer */
	snd_hdac_chip_writew(bus, CORBRP, AZX_CORBRP_RST);
	if (!bus->corbrp_self_clear)
		azx_clear_corbrp(bus);

	/* enable corb dma */
	snd_hdac_chip_writeb(bus, CORBCTL, AZX_CORBCTL_RUN);

	/* RIRB set up */
	bus->rirb.addr = bus->rb.addr + 2048;
	bus->rirb.buf = (__le32 *)(bus->rb.area + 2048);
	bus->rirb.wp = bus->rirb.rp = 0;
	memset(bus->rirb.cmds, 0, sizeof(bus->rirb.cmds));
	snd_hdac_chip_writel(bus, RIRBLBASE, (u32)bus->rirb.addr);
	snd_hdac_chip_writel(bus, RIRBUBASE, upper_32_bits(bus->rirb.addr));

	/* set the rirb size to 256 entries (ULI requires explicitly) */
	snd_hdac_chip_writeb(bus, RIRBSIZE, 0x02);
	/* reset the rirb hw write pointer */
	snd_hdac_chip_writew(bus, RIRBWP, AZX_RIRBWP_RST);
	/* set N=1, get RIRB response interrupt for new entry */
	snd_hdac_chip_writew(bus, RINTCNT, 1);
	/* enable rirb dma and response irq */
	snd_hdac_chip_writeb(bus, RIRBCTL, AZX_RBCTL_DMA_EN | AZX_RBCTL_IRQ_EN);
	/* Accept unsolicited responses */
	snd_hdac_chip_updatel(bus, GCTL, AZX_GCTL_UNSOL, AZX_GCTL_UNSOL);
	spin_unlock_irq(&bus->reg_lock);
}