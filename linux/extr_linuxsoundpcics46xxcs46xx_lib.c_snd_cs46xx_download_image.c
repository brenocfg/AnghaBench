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
struct snd_cs46xx {struct ba1_struct* ba1; } ;
struct ba1_struct {TYPE_1__* memory; int /*<<< orphan*/ * map; } ;
struct TYPE_2__ {int size; int /*<<< orphan*/  offset; } ;

/* Variables and functions */
 int BA1_MEMORY_COUNT ; 
 int snd_cs46xx_download (struct snd_cs46xx*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int snd_cs46xx_download_image(struct snd_cs46xx *chip)
{
	int idx, err;
	unsigned int offset = 0;
	struct ba1_struct *ba1 = chip->ba1;

	for (idx = 0; idx < BA1_MEMORY_COUNT; idx++) {
		err = snd_cs46xx_download(chip,
					  &ba1->map[offset],
					  ba1->memory[idx].offset,
					  ba1->memory[idx].size);
		if (err < 0)
			return err;
		offset += ba1->memory[idx].size >> 2;
	}	
	return 0;
}