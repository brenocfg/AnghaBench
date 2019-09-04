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
struct snd_ca0106 {TYPE_1__* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  I2C_A ; 
 int I2C_A_ADC_ABORT ; 
 int I2C_A_ADC_ADD ; 
 int I2C_A_ADC_LAST ; 
 int I2C_A_ADC_START ; 
 int /*<<< orphan*/  I2C_D1 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int snd_ca0106_ptr_read (struct snd_ca0106*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ca0106_ptr_write (struct snd_ca0106*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int snd_ca0106_i2c_write(struct snd_ca0106 *emu,
				u32 reg,
				u32 value)
{
	u32 tmp;
	int timeout = 0;
	int status;
	int retry;
	if ((reg > 0x7f) || (value > 0x1ff)) {
		dev_err(emu->card->dev, "i2c_write: invalid values.\n");
		return -EINVAL;
	}

	tmp = reg << 25 | value << 16;
	/*
	dev_dbg(emu->card->dev, "I2C-write:reg=0x%x, value=0x%x\n", reg, value);
	*/
	/* Not sure what this I2C channel controls. */
	/* snd_ca0106_ptr_write(emu, I2C_D0, 0, tmp); */

	/* This controls the I2C connected to the WM8775 ADC Codec */
	snd_ca0106_ptr_write(emu, I2C_D1, 0, tmp);

	for (retry = 0; retry < 10; retry++) {
		/* Send the data to i2c */
		//tmp = snd_ca0106_ptr_read(emu, I2C_A, 0);
		//tmp = tmp & ~(I2C_A_ADC_READ|I2C_A_ADC_LAST|I2C_A_ADC_START|I2C_A_ADC_ADD_MASK);
		tmp = 0;
		tmp = tmp | (I2C_A_ADC_LAST|I2C_A_ADC_START|I2C_A_ADC_ADD);
		snd_ca0106_ptr_write(emu, I2C_A, 0, tmp);

		/* Wait till the transaction ends */
		while (1) {
			status = snd_ca0106_ptr_read(emu, I2C_A, 0);
			/*dev_dbg(emu->card->dev, "I2C:status=0x%x\n", status);*/
			timeout++;
			if ((status & I2C_A_ADC_START) == 0)
				break;

			if (timeout > 1000)
				break;
		}
		//Read back and see if the transaction is successful
		if ((status & I2C_A_ADC_ABORT) == 0)
			break;
	}

	if (retry == 10) {
		dev_err(emu->card->dev, "Writing to ADC failed!\n");
		return -EINVAL;
	}
    
    	return 0;
}