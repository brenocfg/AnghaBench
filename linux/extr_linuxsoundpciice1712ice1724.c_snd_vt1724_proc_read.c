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
struct TYPE_4__ {unsigned int size; int /*<<< orphan*/ * data; int /*<<< orphan*/  gpiostate; int /*<<< orphan*/  gpiomask; int /*<<< orphan*/  gpiodir; int /*<<< orphan*/  version; int /*<<< orphan*/  subvendor; } ;
struct snd_ice1712 {scalar_t__ profi_port; scalar_t__ port; TYPE_2__ eeprom; TYPE_1__* card; } ;
struct TYPE_3__ {int /*<<< orphan*/  longname; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICEMT1724 (struct snd_ice1712*,int /*<<< orphan*/ ) ; 
 size_t ICE_EEP2_ACLINK ; 
 size_t ICE_EEP2_I2S ; 
 size_t ICE_EEP2_SPDIF ; 
 size_t ICE_EEP2_SYSCONF ; 
 int /*<<< orphan*/  ROUTE_PLAYBACK ; 
 int /*<<< orphan*/  inb (scalar_t__) ; 
 scalar_t__ inl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_iprintf (struct snd_info_buffer*,char*,...) ; 

__attribute__((used)) static void snd_vt1724_proc_read(struct snd_info_entry *entry,
				 struct snd_info_buffer *buffer)
{
	struct snd_ice1712 *ice = entry->private_data;
	unsigned int idx;

	snd_iprintf(buffer, "%s\n\n", ice->card->longname);
	snd_iprintf(buffer, "EEPROM:\n");

	snd_iprintf(buffer, "  Subvendor        : 0x%x\n", ice->eeprom.subvendor);
	snd_iprintf(buffer, "  Size             : %i bytes\n", ice->eeprom.size);
	snd_iprintf(buffer, "  Version          : %i\n", ice->eeprom.version);
	snd_iprintf(buffer, "  System Config    : 0x%x\n",
		    ice->eeprom.data[ICE_EEP2_SYSCONF]);
	snd_iprintf(buffer, "  ACLink           : 0x%x\n",
		    ice->eeprom.data[ICE_EEP2_ACLINK]);
	snd_iprintf(buffer, "  I2S              : 0x%x\n",
		    ice->eeprom.data[ICE_EEP2_I2S]);
	snd_iprintf(buffer, "  S/PDIF           : 0x%x\n",
		    ice->eeprom.data[ICE_EEP2_SPDIF]);
	snd_iprintf(buffer, "  GPIO direction   : 0x%x\n",
		    ice->eeprom.gpiodir);
	snd_iprintf(buffer, "  GPIO mask        : 0x%x\n",
		    ice->eeprom.gpiomask);
	snd_iprintf(buffer, "  GPIO state       : 0x%x\n",
		    ice->eeprom.gpiostate);
	for (idx = 0x12; idx < ice->eeprom.size; idx++)
		snd_iprintf(buffer, "  Extra #%02i        : 0x%x\n",
			    idx, ice->eeprom.data[idx]);

	snd_iprintf(buffer, "\nRegisters:\n");

	snd_iprintf(buffer, "  PSDOUT03 : 0x%08x\n",
		    (unsigned)inl(ICEMT1724(ice, ROUTE_PLAYBACK)));
	for (idx = 0x0; idx < 0x20 ; idx++)
		snd_iprintf(buffer, "  CCS%02x    : 0x%02x\n",
			    idx, inb(ice->port+idx));
	for (idx = 0x0; idx < 0x30 ; idx++)
		snd_iprintf(buffer, "  MT%02x     : 0x%02x\n",
			    idx, inb(ice->profi_port+idx));
}