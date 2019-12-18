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
struct snd_info_entry {struct snd_ice1712* private_data; } ;
struct snd_info_buffer {int dummy; } ;
struct TYPE_4__ {unsigned int subvendor; unsigned int size; unsigned int version; unsigned int* data; unsigned int gpiomask; unsigned int gpiostate; unsigned int gpiodir; } ;
struct snd_ice1712 {TYPE_2__ eeprom; TYPE_1__* card; } ;
struct TYPE_3__ {unsigned int longname; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICE1712_IREG_GPIO_DIRECTION ; 
 int /*<<< orphan*/  ICE1712_IREG_GPIO_WRITE_MASK ; 
 int /*<<< orphan*/  ICEMT (struct snd_ice1712*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ICE_EEP1_AC97_MAIN_LO ; 
 int /*<<< orphan*/  ICE_EEP1_AC97_PCM_LO ; 
 size_t ICE_EEP1_AC97_RECSRC ; 
 int /*<<< orphan*/  ICE_EEP1_AC97_REC_LO ; 
 size_t ICE_EEP1_ACLINK ; 
 unsigned int ICE_EEP1_ADC_ID ; 
 size_t ICE_EEP1_CODEC ; 
 unsigned int ICE_EEP1_DAC_ID ; 
 size_t ICE_EEP1_I2SID ; 
 size_t ICE_EEP1_SPDIF ; 
 int /*<<< orphan*/  RATE ; 
 int /*<<< orphan*/  ROUTE_CAPTURE ; 
 int /*<<< orphan*/  ROUTE_PSDOUT03 ; 
 int /*<<< orphan*/  ROUTE_SPDOUT ; 
 unsigned int eeprom_double (struct snd_ice1712*,int /*<<< orphan*/ ) ; 
 scalar_t__ inb (int /*<<< orphan*/ ) ; 
 unsigned int inl (int /*<<< orphan*/ ) ; 
 scalar_t__ inw (int /*<<< orphan*/ ) ; 
 scalar_t__ snd_ice1712_get_gpio_data (struct snd_ice1712*) ; 
 scalar_t__ snd_ice1712_read (struct snd_ice1712*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_iprintf (struct snd_info_buffer*,char*,...) ; 

__attribute__((used)) static void snd_ice1712_proc_read(struct snd_info_entry *entry,
				  struct snd_info_buffer *buffer)
{
	struct snd_ice1712 *ice = entry->private_data;
	unsigned int idx;

	snd_iprintf(buffer, "%s\n\n", ice->card->longname);
	snd_iprintf(buffer, "EEPROM:\n");

	snd_iprintf(buffer, "  Subvendor        : 0x%x\n", ice->eeprom.subvendor);
	snd_iprintf(buffer, "  Size             : %i bytes\n", ice->eeprom.size);
	snd_iprintf(buffer, "  Version          : %i\n", ice->eeprom.version);
	snd_iprintf(buffer, "  Codec            : 0x%x\n", ice->eeprom.data[ICE_EEP1_CODEC]);
	snd_iprintf(buffer, "  ACLink           : 0x%x\n", ice->eeprom.data[ICE_EEP1_ACLINK]);
	snd_iprintf(buffer, "  I2S ID           : 0x%x\n", ice->eeprom.data[ICE_EEP1_I2SID]);
	snd_iprintf(buffer, "  S/PDIF           : 0x%x\n", ice->eeprom.data[ICE_EEP1_SPDIF]);
	snd_iprintf(buffer, "  GPIO mask        : 0x%x\n", ice->eeprom.gpiomask);
	snd_iprintf(buffer, "  GPIO state       : 0x%x\n", ice->eeprom.gpiostate);
	snd_iprintf(buffer, "  GPIO direction   : 0x%x\n", ice->eeprom.gpiodir);
	snd_iprintf(buffer, "  AC'97 main       : 0x%x\n", eeprom_double(ice, ICE_EEP1_AC97_MAIN_LO));
	snd_iprintf(buffer, "  AC'97 pcm        : 0x%x\n", eeprom_double(ice, ICE_EEP1_AC97_PCM_LO));
	snd_iprintf(buffer, "  AC'97 record     : 0x%x\n", eeprom_double(ice, ICE_EEP1_AC97_REC_LO));
	snd_iprintf(buffer, "  AC'97 record src : 0x%x\n", ice->eeprom.data[ICE_EEP1_AC97_RECSRC]);
	for (idx = 0; idx < 4; idx++)
		snd_iprintf(buffer, "  DAC ID #%i        : 0x%x\n", idx, ice->eeprom.data[ICE_EEP1_DAC_ID + idx]);
	for (idx = 0; idx < 4; idx++)
		snd_iprintf(buffer, "  ADC ID #%i        : 0x%x\n", idx, ice->eeprom.data[ICE_EEP1_ADC_ID + idx]);
	for (idx = 0x1c; idx < ice->eeprom.size; idx++)
		snd_iprintf(buffer, "  Extra #%02i        : 0x%x\n", idx, ice->eeprom.data[idx]);

	snd_iprintf(buffer, "\nRegisters:\n");
	snd_iprintf(buffer, "  PSDOUT03         : 0x%04x\n", (unsigned)inw(ICEMT(ice, ROUTE_PSDOUT03)));
	snd_iprintf(buffer, "  CAPTURE          : 0x%08x\n", inl(ICEMT(ice, ROUTE_CAPTURE)));
	snd_iprintf(buffer, "  SPDOUT           : 0x%04x\n", (unsigned)inw(ICEMT(ice, ROUTE_SPDOUT)));
	snd_iprintf(buffer, "  RATE             : 0x%02x\n", (unsigned)inb(ICEMT(ice, RATE)));
	snd_iprintf(buffer, "  GPIO_DATA        : 0x%02x\n", (unsigned)snd_ice1712_get_gpio_data(ice));
	snd_iprintf(buffer, "  GPIO_WRITE_MASK  : 0x%02x\n", (unsigned)snd_ice1712_read(ice, ICE1712_IREG_GPIO_WRITE_MASK));
	snd_iprintf(buffer, "  GPIO_DIRECTION   : 0x%02x\n", (unsigned)snd_ice1712_read(ice, ICE1712_IREG_GPIO_DIRECTION));
}