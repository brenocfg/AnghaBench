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
typedef  struct firmware const firmware ;
struct echoaudio {struct firmware const** fw_cache; TYPE_2__* card; TYPE_1__* pci; } ;
typedef  int /*<<< orphan*/  name ;
struct TYPE_6__ {char* data; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 TYPE_3__* card_fw ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int request_firmware (struct firmware const**,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 

__attribute__((used)) static int get_firmware(const struct firmware **fw_entry,
			struct echoaudio *chip, const short fw_index)
{
	int err;
	char name[30];

#ifdef CONFIG_PM_SLEEP
	if (chip->fw_cache[fw_index]) {
		dev_dbg(chip->card->dev,
			"firmware requested: %s is cached\n",
			card_fw[fw_index].data);
		*fw_entry = chip->fw_cache[fw_index];
		return 0;
	}
#endif

	dev_dbg(chip->card->dev,
		"firmware requested: %s\n", card_fw[fw_index].data);
	snprintf(name, sizeof(name), "ea/%s", card_fw[fw_index].data);
	err = request_firmware(fw_entry, name, &chip->pci->dev);
	if (err < 0)
		dev_err(chip->card->dev,
			"get_firmware(): Firmware not available (%d)\n", err);
#ifdef CONFIG_PM_SLEEP
	else
		chip->fw_cache[fw_index] = *fw_entry;
#endif
	return err;
}