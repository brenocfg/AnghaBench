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
struct net_device {unsigned int base_addr; int irq; int mem_start; int mem_end; int /*<<< orphan*/  name; } ;
struct ifmap {unsigned int base_addr; int irq; unsigned int mem_start; } ;
struct frad_local {int initialized; int type; char state; } ;

/* Variables and functions */
 int ARRAY_SIZE (unsigned int*) ; 
 int EAGAIN ; 
 int EINVAL ; 
 int ENODEV ; 
 char SDLA_8K_WINDOW ; 
 char SDLA_HALT ; 
 int SDLA_IO_EXTENTS ; 
 char SDLA_MEMEN ; 
 scalar_t__ SDLA_REG_CONTROL ; 
 scalar_t__ SDLA_REG_PC_WINDOW ; 
 scalar_t__ SDLA_REG_Z80_CONTROL ; 
#define  SDLA_S502A 131 
 char SDLA_S502A_HALT ; 
 char SDLA_S502A_INTEN ; 
 char SDLA_S502A_START ; 
#define  SDLA_S502E 130 
 char SDLA_S502E_ENABLE ; 
 char SDLA_S502E_INTACK ; 
 char SDLA_S502_SEG_A ; 
 char SDLA_S502_SEG_C ; 
 char SDLA_S502_SEG_D ; 
 char SDLA_S502_SEG_E ; 
 unsigned int SDLA_S502_STS ; 
#define  SDLA_S507 129 
 char SDLA_S507_ENABLE ; 
 char SDLA_S507_IRQ10 ; 
 char SDLA_S507_IRQ11 ; 
 char SDLA_S507_IRQ12 ; 
 char SDLA_S507_IRQ15 ; 
 char SDLA_S507_IRQ3 ; 
 char SDLA_S507_IRQ4 ; 
 char SDLA_S507_IRQ5 ; 
 char SDLA_S507_IRQ7 ; 
 char SDLA_S507_SEG_A ; 
 char SDLA_S507_SEG_B ; 
 char SDLA_S507_SEG_C ; 
 char SDLA_S507_SEG_E ; 
#define  SDLA_S508 128 
 char SDLA_S508_INTEN ; 
 char SDLA_S508_SEG_A ; 
 char SDLA_S508_SEG_C ; 
 char SDLA_S508_SEG_D ; 
 char SDLA_S508_SEG_E ; 
 unsigned int SDLA_S508_STS ; 
 int SDLA_UNKNOWN ; 
 int /*<<< orphan*/  free_irq (int,struct net_device*) ; 
 int inb (unsigned int) ; 
 int /*<<< orphan*/  netdev_notice (struct net_device*,char*) ; 
 struct frad_local* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  outb (char,scalar_t__) ; 
 int /*<<< orphan*/  pr_warn (char*,unsigned int) ; 
 int /*<<< orphan*/  release_region (unsigned int,int) ; 
 scalar_t__ request_irq (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  request_region (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdla_isr ; 
 unsigned int* valid_mem ; 
 unsigned int* valid_port ; 

__attribute__((used)) static int sdla_set_config(struct net_device *dev, struct ifmap *map)
{
	struct frad_local *flp;
	int               i;
	char              byte;
	unsigned base;
	int err = -EINVAL;

	flp = netdev_priv(dev);

	if (flp->initialized)
		return -EINVAL;

	for(i=0; i < ARRAY_SIZE(valid_port); i++)
		if (valid_port[i] == map->base_addr)
			break;   

	if (i == ARRAY_SIZE(valid_port))
		return -EINVAL;

	if (!request_region(map->base_addr, SDLA_IO_EXTENTS, dev->name)){
		pr_warn("io-port 0x%04lx in use\n", dev->base_addr);
		return -EINVAL;
	}
	base = map->base_addr;

	/* test for card types, S502A, S502E, S507, S508                 */
	/* these tests shut down the card completely, so clear the state */
	flp->type = SDLA_UNKNOWN;
	flp->state = 0;
   
	for(i=1;i<SDLA_IO_EXTENTS;i++)
		if (inb(base + i) != 0xFF)
			break;

	if (i == SDLA_IO_EXTENTS) {   
		outb(SDLA_HALT, base + SDLA_REG_Z80_CONTROL);
		if ((inb(base + SDLA_S502_STS) & 0x0F) == 0x08) {
			outb(SDLA_S502E_INTACK, base + SDLA_REG_CONTROL);
			if ((inb(base + SDLA_S502_STS) & 0x0F) == 0x0C) {
				outb(SDLA_HALT, base + SDLA_REG_CONTROL);
				flp->type = SDLA_S502E;
				goto got_type;
			}
		}
	}

	for(byte=inb(base),i=0;i<SDLA_IO_EXTENTS;i++)
		if (inb(base + i) != byte)
			break;

	if (i == SDLA_IO_EXTENTS) {
		outb(SDLA_HALT, base + SDLA_REG_CONTROL);
		if ((inb(base + SDLA_S502_STS) & 0x7E) == 0x30) {
			outb(SDLA_S507_ENABLE, base + SDLA_REG_CONTROL);
			if ((inb(base + SDLA_S502_STS) & 0x7E) == 0x32) {
				outb(SDLA_HALT, base + SDLA_REG_CONTROL);
				flp->type = SDLA_S507;
				goto got_type;
			}
		}
	}

	outb(SDLA_HALT, base + SDLA_REG_CONTROL);
	if ((inb(base + SDLA_S508_STS) & 0x3F) == 0x00) {
		outb(SDLA_S508_INTEN, base + SDLA_REG_CONTROL);
		if ((inb(base + SDLA_S508_STS) & 0x3F) == 0x10) {
			outb(SDLA_HALT, base + SDLA_REG_CONTROL);
			flp->type = SDLA_S508;
			goto got_type;
		}
	}

	outb(SDLA_S502A_HALT, base + SDLA_REG_CONTROL);
	if (inb(base + SDLA_S502_STS) == 0x40) {
		outb(SDLA_S502A_START, base + SDLA_REG_CONTROL);
		if (inb(base + SDLA_S502_STS) == 0x40) {
			outb(SDLA_S502A_INTEN, base + SDLA_REG_CONTROL);
			if (inb(base + SDLA_S502_STS) == 0x44) {
				outb(SDLA_S502A_START, base + SDLA_REG_CONTROL);
				flp->type = SDLA_S502A;
				goto got_type;
			}
		}
	}

	netdev_notice(dev, "Unknown card type\n");
	err = -ENODEV;
	goto fail;

got_type:
	switch(base) {
		case 0x270:
		case 0x280:
		case 0x380: 
		case 0x390:
			if (flp->type != SDLA_S508 && flp->type != SDLA_S507)
				goto fail;
	}

	switch (map->irq) {
		case 2:
			if (flp->type != SDLA_S502E)
				goto fail;
			break;

		case 10:
		case 11:
		case 12:
		case 15:
		case 4:
			if (flp->type != SDLA_S508 && flp->type != SDLA_S507)
				goto fail;
			break;
		case 3:
		case 5:
		case 7:
			if (flp->type == SDLA_S502A)
				goto fail;
			break;

		default:
			goto fail;
	}

	err = -EAGAIN;
	if (request_irq(dev->irq, sdla_isr, 0, dev->name, dev)) 
		goto fail;

	if (flp->type == SDLA_S507) {
		switch(dev->irq) {
			case 3:
				flp->state = SDLA_S507_IRQ3;
				break;
			case 4:
				flp->state = SDLA_S507_IRQ4;
				break;
			case 5:
				flp->state = SDLA_S507_IRQ5;
				break;
			case 7:
				flp->state = SDLA_S507_IRQ7;
				break;
			case 10:
				flp->state = SDLA_S507_IRQ10;
				break;
			case 11:
				flp->state = SDLA_S507_IRQ11;
				break;
			case 12:
				flp->state = SDLA_S507_IRQ12;
				break;
			case 15:
				flp->state = SDLA_S507_IRQ15;
				break;
		}
	}

	for(i=0; i < ARRAY_SIZE(valid_mem); i++)
		if (valid_mem[i] == map->mem_start)
			break;   

	err = -EINVAL;
	if (i == ARRAY_SIZE(valid_mem))
		goto fail2;

	if (flp->type == SDLA_S502A && (map->mem_start & 0xF000) >> 12 == 0x0E)
		goto fail2;

	if (flp->type != SDLA_S507 && map->mem_start >> 16 == 0x0B)
		goto fail2;

	if (flp->type == SDLA_S507 && map->mem_start >> 16 == 0x0D)
		goto fail2;

	byte = flp->type != SDLA_S508 ? SDLA_8K_WINDOW : 0;
	byte |= (map->mem_start & 0xF000) >> (12 + (flp->type == SDLA_S508 ? 1 : 0));
	switch(flp->type) {
		case SDLA_S502A:
		case SDLA_S502E:
			switch (map->mem_start >> 16) {
				case 0x0A:
					byte |= SDLA_S502_SEG_A;
					break;
				case 0x0C:
					byte |= SDLA_S502_SEG_C;
					break;
				case 0x0D:
					byte |= SDLA_S502_SEG_D;
					break;
				case 0x0E:
					byte |= SDLA_S502_SEG_E;
					break;
			}
			break;
		case SDLA_S507:
			switch (map->mem_start >> 16) {
				case 0x0A:
					byte |= SDLA_S507_SEG_A;
					break;
				case 0x0B:
					byte |= SDLA_S507_SEG_B;
					break;
				case 0x0C:
					byte |= SDLA_S507_SEG_C;
					break;
				case 0x0E:
					byte |= SDLA_S507_SEG_E;
					break;
			}
			break;
		case SDLA_S508:
			switch (map->mem_start >> 16) {
				case 0x0A:
					byte |= SDLA_S508_SEG_A;
					break;
				case 0x0C:
					byte |= SDLA_S508_SEG_C;
					break;
				case 0x0D:
					byte |= SDLA_S508_SEG_D;
					break;
				case 0x0E:
					byte |= SDLA_S508_SEG_E;
					break;
			}
			break;
	}

	/* set the memory bits, and enable access */
	outb(byte, base + SDLA_REG_PC_WINDOW);

	switch(flp->type)
	{
		case SDLA_S502E:
			flp->state = SDLA_S502E_ENABLE;
			break;
		case SDLA_S507:
			flp->state |= SDLA_MEMEN;
			break;
		case SDLA_S508:
			flp->state = SDLA_MEMEN;
			break;
	}
	outb(flp->state, base + SDLA_REG_CONTROL);

	dev->irq = map->irq;
	dev->base_addr = base;
	dev->mem_start = map->mem_start;
	dev->mem_end = dev->mem_start + 0x2000;
	flp->initialized = 1;
	return 0;

fail2:
	free_irq(map->irq, dev);
fail:
	release_region(base, SDLA_IO_EXTENTS);
	return err;
}