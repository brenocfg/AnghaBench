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
struct snd_info_entry {struct oxygen* private_data; } ;
struct snd_info_buffer {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* dump_registers ) (struct oxygen*,struct snd_info_buffer*) ;} ;
struct oxygen {TYPE_1__ model; int /*<<< orphan*/  mutex; scalar_t__ has_ac97_1; scalar_t__ has_ac97_0; } ;

/* Variables and functions */
 int OXYGEN_IO_SIZE ; 
#define  OXYGEN_PACKAGE_ID_8786 130 
#define  OXYGEN_PACKAGE_ID_8787 129 
#define  OXYGEN_PACKAGE_ID_8788 128 
 int OXYGEN_PACKAGE_ID_MASK ; 
 int OXYGEN_REVISION ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int oxygen_read8 (struct oxygen*,int) ; 
 int /*<<< orphan*/  oxygen_read_ac97 (struct oxygen*,int,int) ; 
 int /*<<< orphan*/  snd_iprintf (struct snd_info_buffer*,char*,...) ; 
 int /*<<< orphan*/  stub1 (struct oxygen*,struct snd_info_buffer*) ; 

__attribute__((used)) static void oxygen_proc_read(struct snd_info_entry *entry,
			     struct snd_info_buffer *buffer)
{
	struct oxygen *chip = entry->private_data;
	int i, j;

	switch (oxygen_read8(chip, OXYGEN_REVISION) & OXYGEN_PACKAGE_ID_MASK) {
	case OXYGEN_PACKAGE_ID_8786: i = '6'; break;
	case OXYGEN_PACKAGE_ID_8787: i = '7'; break;
	case OXYGEN_PACKAGE_ID_8788: i = '8'; break;
	default:                     i = '?'; break;
	}
	snd_iprintf(buffer, "CMI878%c:\n", i);
	for (i = 0; i < OXYGEN_IO_SIZE; i += 0x10) {
		snd_iprintf(buffer, "%02x:", i);
		for (j = 0; j < 0x10; ++j)
			snd_iprintf(buffer, " %02x", oxygen_read8(chip, i + j));
		snd_iprintf(buffer, "\n");
	}
	if (mutex_lock_interruptible(&chip->mutex) < 0)
		return;
	if (chip->has_ac97_0) {
		snd_iprintf(buffer, "\nAC97:\n");
		for (i = 0; i < 0x80; i += 0x10) {
			snd_iprintf(buffer, "%02x:", i);
			for (j = 0; j < 0x10; j += 2)
				snd_iprintf(buffer, " %04x",
					    oxygen_read_ac97(chip, 0, i + j));
			snd_iprintf(buffer, "\n");
		}
	}
	if (chip->has_ac97_1) {
		snd_iprintf(buffer, "\nAC97 2:\n");
		for (i = 0; i < 0x80; i += 0x10) {
			snd_iprintf(buffer, "%02x:", i);
			for (j = 0; j < 0x10; j += 2)
				snd_iprintf(buffer, " %04x",
					    oxygen_read_ac97(chip, 1, i + j));
			snd_iprintf(buffer, "\n");
		}
	}
	mutex_unlock(&chip->mutex);
	if (chip->model.dump_registers)
		chip->model.dump_registers(chip, buffer);
}