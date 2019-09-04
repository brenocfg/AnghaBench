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
struct snd_emu10k1 {int /*<<< orphan*/  i2c_lock; TYPE_1__* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int I2C_A_ADC_ABORT ; 
 int I2C_A_ADC_ADD ; 
 int I2C_A_ADC_LAST ; 
 int I2C_A_ADC_START ; 
 int /*<<< orphan*/  P17V_I2C_1 ; 
 int /*<<< orphan*/  P17V_I2C_ADDR ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int snd_emu10k1_ptr20_read (struct snd_emu10k1*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_emu10k1_ptr20_write (struct snd_emu10k1*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int snd_emu10k1_i2c_write(struct snd_emu10k1 *emu,
				u32 reg,
				u32 value)
{
	u32 tmp;
	int timeout = 0;
	int status;
	int retry;
	int err = 0;

	if ((reg > 0x7f) || (value > 0x1ff)) {
		dev_err(emu->card->dev, "i2c_write: invalid values.\n");
		return -EINVAL;
	}

	/* This function is not re-entrant, so protect against it. */
	spin_lock(&emu->i2c_lock);

	tmp = reg << 25 | value << 16;

	/* This controls the I2C connected to the WM8775 ADC Codec */
	snd_emu10k1_ptr20_write(emu, P17V_I2C_1, 0, tmp);
	tmp = snd_emu10k1_ptr20_read(emu, P17V_I2C_1, 0); /* write post */

	for (retry = 0; retry < 10; retry++) {
		/* Send the data to i2c */
		tmp = 0;
		tmp = tmp | (I2C_A_ADC_LAST|I2C_A_ADC_START|I2C_A_ADC_ADD);
		snd_emu10k1_ptr20_write(emu, P17V_I2C_ADDR, 0, tmp);

		/* Wait till the transaction ends */
		while (1) {
			mdelay(1);
			status = snd_emu10k1_ptr20_read(emu, P17V_I2C_ADDR, 0);
			timeout++;
			if ((status & I2C_A_ADC_START) == 0)
				break;

			if (timeout > 1000) {
				dev_warn(emu->card->dev,
					   "emu10k1:I2C:timeout status=0x%x\n",
					   status);
				break;
			}
		}
		//Read back and see if the transaction is successful
		if ((status & I2C_A_ADC_ABORT) == 0)
			break;
	}

	if (retry == 10) {
		dev_err(emu->card->dev, "Writing to ADC failed!\n");
		dev_err(emu->card->dev, "status=0x%x, reg=%d, value=%d\n",
			status, reg, value);
		/* dump_stack(); */
		err = -EINVAL;
	}
    
	spin_unlock(&emu->i2c_lock);
	return err;
}