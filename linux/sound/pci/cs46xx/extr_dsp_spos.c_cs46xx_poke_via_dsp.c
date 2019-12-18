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
typedef  int u32 ;
struct snd_cs46xx {TYPE_1__* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int SPIOWRITE_SCB_ADDR ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int snd_cs46xx_peek (struct snd_cs46xx*,int) ; 
 int /*<<< orphan*/  snd_cs46xx_poke (struct snd_cs46xx*,int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

int cs46xx_poke_via_dsp (struct snd_cs46xx *chip, u32 address, u32 data)
{
	u32 temp;
	int  i;

	/* santiy check the parameters.  (These numbers are not 100% correct.  They are
	   a rough guess from looking at the controller spec.) */
	if (address < 0x8000 || address >= 0x9000)
		return -EINVAL;
        
	/* initialize the SP_IO_WRITE SCB with the data. */
	temp = ( address << 16 ) | ( address & 0x0000FFFF);   /* offset 0 <-- address2 : address1 */

	snd_cs46xx_poke(chip,( SPIOWRITE_SCB_ADDR      << 2), temp);
	snd_cs46xx_poke(chip,((SPIOWRITE_SCB_ADDR + 1) << 2), data); /* offset 1 <-- data1 */
	snd_cs46xx_poke(chip,((SPIOWRITE_SCB_ADDR + 2) << 2), data); /* offset 1 <-- data2 */
    
	/* Poke this location to tell the task to start */
	snd_cs46xx_poke(chip,((SPIOWRITE_SCB_ADDR + 6) << 2), SPIOWRITE_SCB_ADDR << 0x10);

	/* Verify that the task ran */
	for (i=0; i<25; i++) {
		udelay(125);

		temp =  snd_cs46xx_peek(chip,((SPIOWRITE_SCB_ADDR + 6) << 2));
		if (temp == 0x00000000)
			break;
	}

	if (i == 25) {
		dev_err(chip->card->dev,
			"dsp_spos: SPIOWriteTask not responding\n");
		return -EBUSY;
	}

	return 0;
}