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
struct TYPE_4__ {scalar_t__ subvendor; int* data; int gpiomask; int gpiodir; int gpiostate; } ;
struct TYPE_3__ {int write_mask; int direction; } ;
struct snd_ice1712 {TYPE_2__ eeprom; TYPE_1__ gpio; int /*<<< orphan*/  pci; int /*<<< orphan*/  dxr_enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC97_CMD ; 
 int /*<<< orphan*/  CONTROL ; 
 int ICE1712_AC97_WARM ; 
 int ICE1712_CFG_2xMPU401 ; 
 int ICE1712_CFG_NO_CON_AC97 ; 
 int /*<<< orphan*/  ICE1712_IREG_CONSUMER_POWERDOWN ; 
 int /*<<< orphan*/  ICE1712_IREG_GPIO_DATA ; 
 int /*<<< orphan*/  ICE1712_IREG_GPIO_DIRECTION ; 
 int /*<<< orphan*/  ICE1712_IREG_GPIO_WRITE_MASK ; 
 int /*<<< orphan*/  ICE1712_IREG_PRO_POWERDOWN ; 
 int ICE1712_IRQ_CONCAP ; 
 int ICE1712_IRQ_CONPBK ; 
 int ICE1712_IRQ_MPU2 ; 
 int ICE1712_IRQ_PBKDS ; 
 int ICE1712_NATIVE ; 
 int ICE1712_RESET ; 
 int ICE1712_STDSP24_CLOCK_BIT ; 
 scalar_t__ ICE1712_SUBDEVICE_DMX6FIRE ; 
 scalar_t__ ICE1712_SUBDEVICE_STDSP24 ; 
 int /*<<< orphan*/  ICEMT (struct snd_ice1712*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ICEREG (struct snd_ice1712*,int /*<<< orphan*/ ) ; 
 size_t ICE_EEP1_ACLINK ; 
 size_t ICE_EEP1_CODEC ; 
 size_t ICE_EEP1_I2SID ; 
 size_t ICE_EEP1_SPDIF ; 
 int /*<<< orphan*/  IRQ ; 
 int /*<<< orphan*/  IRQMASK ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_write_config_byte (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  snd_ice1712_set_pro_rate (struct snd_ice1712*,int,int) ; 
 int /*<<< orphan*/  snd_ice1712_write (struct snd_ice1712*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int snd_ice1712_chip_init(struct snd_ice1712 *ice)
{
	outb(ICE1712_RESET | ICE1712_NATIVE, ICEREG(ice, CONTROL));
	udelay(200);
	outb(ICE1712_NATIVE, ICEREG(ice, CONTROL));
	udelay(200);
	if (ice->eeprom.subvendor == ICE1712_SUBDEVICE_DMX6FIRE &&
	    !ice->dxr_enable)
		/*  Set eeprom value to limit active ADCs and DACs to 6;
		 *  Also disable AC97 as no hardware in standard 6fire card/box
		 *  Note: DXR extensions are not currently supported
		 */
		ice->eeprom.data[ICE_EEP1_CODEC] = 0x3a;
	pci_write_config_byte(ice->pci, 0x60, ice->eeprom.data[ICE_EEP1_CODEC]);
	pci_write_config_byte(ice->pci, 0x61, ice->eeprom.data[ICE_EEP1_ACLINK]);
	pci_write_config_byte(ice->pci, 0x62, ice->eeprom.data[ICE_EEP1_I2SID]);
	pci_write_config_byte(ice->pci, 0x63, ice->eeprom.data[ICE_EEP1_SPDIF]);
	if (ice->eeprom.subvendor != ICE1712_SUBDEVICE_STDSP24) {
		ice->gpio.write_mask = ice->eeprom.gpiomask;
		ice->gpio.direction = ice->eeprom.gpiodir;
		snd_ice1712_write(ice, ICE1712_IREG_GPIO_WRITE_MASK,
				  ice->eeprom.gpiomask);
		snd_ice1712_write(ice, ICE1712_IREG_GPIO_DIRECTION,
				  ice->eeprom.gpiodir);
		snd_ice1712_write(ice, ICE1712_IREG_GPIO_DATA,
				  ice->eeprom.gpiostate);
	} else {
		ice->gpio.write_mask = 0xc0;
		ice->gpio.direction = 0xff;
		snd_ice1712_write(ice, ICE1712_IREG_GPIO_WRITE_MASK, 0xc0);
		snd_ice1712_write(ice, ICE1712_IREG_GPIO_DIRECTION, 0xff);
		snd_ice1712_write(ice, ICE1712_IREG_GPIO_DATA,
				  ICE1712_STDSP24_CLOCK_BIT);
	}
	snd_ice1712_write(ice, ICE1712_IREG_PRO_POWERDOWN, 0);
	if (!(ice->eeprom.data[ICE_EEP1_CODEC] & ICE1712_CFG_NO_CON_AC97)) {
		outb(ICE1712_AC97_WARM, ICEREG(ice, AC97_CMD));
		udelay(100);
		outb(0, ICEREG(ice, AC97_CMD));
		udelay(200);
		snd_ice1712_write(ice, ICE1712_IREG_CONSUMER_POWERDOWN, 0);
	}
	snd_ice1712_set_pro_rate(ice, 48000, 1);
	/* unmask used interrupts */
	outb(((ice->eeprom.data[ICE_EEP1_CODEC] & ICE1712_CFG_2xMPU401) == 0 ?
	      ICE1712_IRQ_MPU2 : 0) |
	     ((ice->eeprom.data[ICE_EEP1_CODEC] & ICE1712_CFG_NO_CON_AC97) ?
	      ICE1712_IRQ_PBKDS | ICE1712_IRQ_CONCAP | ICE1712_IRQ_CONPBK : 0),
	     ICEREG(ice, IRQMASK));
	outb(0x00, ICEMT(ice, IRQ));

	return 0;
}