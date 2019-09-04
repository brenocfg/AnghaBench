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
typedef  int /*<<< orphan*/  vendor ;
typedef  int /*<<< orphan*/  u32 ;
struct snd_dice {TYPE_1__* unit; struct snd_card* card; } ;
struct snd_card {char* driver; char* shortname; char* mixername; int /*<<< orphan*/  longname; } ;
struct fw_device {int* config_rom; int max_speed; } ;
typedef  int /*<<< orphan*/  model ;
struct TYPE_2__ {int* directory; int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  CSR_MODEL ; 
 int /*<<< orphan*/  CSR_VENDOR ; 
 int /*<<< orphan*/  GLOBAL_NICK_NAME ; 
 int NICK_NAME_SIZE ; 
 char* dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fw_csr_string (int*,int /*<<< orphan*/ ,char*,int) ; 
 struct fw_device* fw_parent_device (TYPE_1__*) ; 
 int snd_dice_transaction_read_global (struct snd_dice*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*,char*,int,char*,int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  swab32s (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dice_card_strings(struct snd_dice *dice)
{
	struct snd_card *card = dice->card;
	struct fw_device *dev = fw_parent_device(dice->unit);
	char vendor[32], model[32];
	unsigned int i;
	int err;

	strcpy(card->driver, "DICE");

	strcpy(card->shortname, "DICE");
	BUILD_BUG_ON(NICK_NAME_SIZE < sizeof(card->shortname));
	err = snd_dice_transaction_read_global(dice, GLOBAL_NICK_NAME,
					       card->shortname,
					       sizeof(card->shortname));
	if (err >= 0) {
		/* DICE strings are returned in "always-wrong" endianness */
		BUILD_BUG_ON(sizeof(card->shortname) % 4 != 0);
		for (i = 0; i < sizeof(card->shortname); i += 4)
			swab32s((u32 *)&card->shortname[i]);
		card->shortname[sizeof(card->shortname) - 1] = '\0';
	}

	strcpy(vendor, "?");
	fw_csr_string(dev->config_rom + 5, CSR_VENDOR, vendor, sizeof(vendor));
	strcpy(model, "?");
	fw_csr_string(dice->unit->directory, CSR_MODEL, model, sizeof(model));
	snprintf(card->longname, sizeof(card->longname),
		 "%s %s (serial %u) at %s, S%d",
		 vendor, model, dev->config_rom[4] & 0x3fffff,
		 dev_name(&dice->unit->device), 100 << dev->max_speed);

	strcpy(card->mixername, "DICE");
}