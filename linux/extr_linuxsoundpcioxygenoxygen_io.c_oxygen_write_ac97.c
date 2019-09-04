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
typedef  unsigned int u32 ;
typedef  void* u16 ;
struct oxygen {TYPE_1__* card; void*** saved_ac97_registers; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  OXYGEN_AC97_INT_WRITE_DONE ; 
 int /*<<< orphan*/  OXYGEN_AC97_REGS ; 
 unsigned int OXYGEN_AC97_REG_ADDR_SHIFT ; 
 unsigned int OXYGEN_AC97_REG_CODEC_SHIFT ; 
 unsigned int OXYGEN_AC97_REG_DIR_WRITE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ oxygen_ac97_wait (struct oxygen*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oxygen_write32 (struct oxygen*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  udelay (int) ; 

void oxygen_write_ac97(struct oxygen *chip, unsigned int codec,
		       unsigned int index, u16 data)
{
	unsigned int count, succeeded;
	u32 reg;

	reg = data;
	reg |= index << OXYGEN_AC97_REG_ADDR_SHIFT;
	reg |= OXYGEN_AC97_REG_DIR_WRITE;
	reg |= codec << OXYGEN_AC97_REG_CODEC_SHIFT;
	succeeded = 0;
	for (count = 5; count > 0; --count) {
		udelay(5);
		oxygen_write32(chip, OXYGEN_AC97_REGS, reg);
		/* require two "completed" writes, just to be sure */
		if (oxygen_ac97_wait(chip, OXYGEN_AC97_INT_WRITE_DONE) >= 0 &&
		    ++succeeded >= 2) {
			chip->saved_ac97_registers[codec][index / 2] = data;
			return;
		}
	}
	dev_err(chip->card->dev, "AC'97 write timeout\n");
}