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
typedef  int /*<<< orphan*/  u16 ;
struct snd_ice1712_card_info {int subvendor; int eeprom_size; int /*<<< orphan*/  eeprom_data; int /*<<< orphan*/  name; scalar_t__ model; } ;
struct TYPE_4__ {int subvendor; int version; int size; int* data; int gpiomask; int gpiostate; int gpiodir; } ;
struct snd_ice1712 {TYPE_2__ eeprom; TYPE_1__* card; int /*<<< orphan*/  pci; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int ENXIO ; 
 int /*<<< orphan*/  I2C_CTRL ; 
 int ICE1712_I2C_EEPROM ; 
 int /*<<< orphan*/  ICEREG (struct snd_ice1712*,int /*<<< orphan*/ ) ; 
 size_t ICE_EEP1_GPIO_DIR ; 
 size_t ICE_EEP1_GPIO_MASK ; 
 size_t ICE_EEP1_GPIO_STATE ; 
 int ICE_I2C_EEPROM_ADDR ; 
 int /*<<< orphan*/  PCI_SUBSYSTEM_ID ; 
 int /*<<< orphan*/  PCI_SUBSYSTEM_VENDOR_ID ; 
 struct snd_ice1712_card_info** card_tables ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_read_config_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int snd_ice1712_read_i2c (struct snd_ice1712*,int,unsigned int) ; 
 int /*<<< orphan*/  strcmp (char const*,scalar_t__) ; 
 unsigned int swab16 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_ice1712_read_eeprom(struct snd_ice1712 *ice,
				   const char *modelname)
{
	int dev = ICE_I2C_EEPROM_ADDR;	/* I2C EEPROM device address */
	unsigned int i, size;
	struct snd_ice1712_card_info * const *tbl, *c;

	if (!modelname || !*modelname) {
		ice->eeprom.subvendor = 0;
		if ((inb(ICEREG(ice, I2C_CTRL)) & ICE1712_I2C_EEPROM) != 0)
			ice->eeprom.subvendor = (snd_ice1712_read_i2c(ice, dev, 0x00) << 0) |
				(snd_ice1712_read_i2c(ice, dev, 0x01) << 8) |
				(snd_ice1712_read_i2c(ice, dev, 0x02) << 16) |
				(snd_ice1712_read_i2c(ice, dev, 0x03) << 24);
		if (ice->eeprom.subvendor == 0 ||
		    ice->eeprom.subvendor == (unsigned int)-1) {
			/* invalid subvendor from EEPROM, try the PCI subststem ID instead */
			u16 vendor, device;
			pci_read_config_word(ice->pci, PCI_SUBSYSTEM_VENDOR_ID, &vendor);
			pci_read_config_word(ice->pci, PCI_SUBSYSTEM_ID, &device);
			ice->eeprom.subvendor = ((unsigned int)swab16(vendor) << 16) | swab16(device);
			if (ice->eeprom.subvendor == 0 || ice->eeprom.subvendor == (unsigned int)-1) {
				dev_err(ice->card->dev,
					"No valid ID is found\n");
				return -ENXIO;
			}
		}
	}
	for (tbl = card_tables; *tbl; tbl++) {
		for (c = *tbl; c->subvendor; c++) {
			if (modelname && c->model && !strcmp(modelname, c->model)) {
				dev_info(ice->card->dev,
					 "Using board model %s\n", c->name);
				ice->eeprom.subvendor = c->subvendor;
			} else if (c->subvendor != ice->eeprom.subvendor)
				continue;
			if (!c->eeprom_size || !c->eeprom_data)
				goto found;
			/* if the EEPROM is given by the driver, use it */
			dev_dbg(ice->card->dev, "using the defined eeprom..\n");
			ice->eeprom.version = 1;
			ice->eeprom.size = c->eeprom_size + 6;
			memcpy(ice->eeprom.data, c->eeprom_data, c->eeprom_size);
			goto read_skipped;
		}
	}
	dev_warn(ice->card->dev, "No matching model found for ID 0x%x\n",
	       ice->eeprom.subvendor);

 found:
	ice->eeprom.size = snd_ice1712_read_i2c(ice, dev, 0x04);
	if (ice->eeprom.size < 6)
		ice->eeprom.size = 32; /* FIXME: any cards without the correct size? */
	else if (ice->eeprom.size > 32) {
		dev_err(ice->card->dev,
			"invalid EEPROM (size = %i)\n", ice->eeprom.size);
		return -EIO;
	}
	ice->eeprom.version = snd_ice1712_read_i2c(ice, dev, 0x05);
	if (ice->eeprom.version != 1) {
		dev_err(ice->card->dev, "invalid EEPROM version %i\n",
			   ice->eeprom.version);
		/* return -EIO; */
	}
	size = ice->eeprom.size - 6;
	for (i = 0; i < size; i++)
		ice->eeprom.data[i] = snd_ice1712_read_i2c(ice, dev, i + 6);

 read_skipped:
	ice->eeprom.gpiomask = ice->eeprom.data[ICE_EEP1_GPIO_MASK];
	ice->eeprom.gpiostate = ice->eeprom.data[ICE_EEP1_GPIO_STATE];
	ice->eeprom.gpiodir = ice->eeprom.data[ICE_EEP1_GPIO_DIR];

	return 0;
}