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
struct hw {scalar_t__ model; TYPE_1__* card; } ;
struct adc_conf {int msr; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADC_LINEIN ; 
 scalar_t__ CTSB1270 ; 
 int EINVAL ; 
 int /*<<< orphan*/  GPIO_CTRL ; 
 int /*<<< orphan*/  GPIO_DATA ; 
 int /*<<< orphan*/  MAKE_WM8775_ADDR (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MAKE_WM8775_DATA (int) ; 
 int /*<<< orphan*/  WM8775_IC ; 
 int /*<<< orphan*/  WM8775_MMC ; 
 int /*<<< orphan*/  dev_alert (int /*<<< orphan*/ ,char*,...) ; 
 int hw20k2_i2c_init (struct hw*,int,int,int) ; 
 int /*<<< orphan*/  hw20k2_i2c_uninit (struct hw*) ; 
 int /*<<< orphan*/  hw20k2_i2c_write (struct hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_adc_input_select (struct hw*,int /*<<< orphan*/ ) ; 
 int hw_read_20kx (struct hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_wm8775_input_select (struct hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_write_20kx (struct hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int hw_adc_init(struct hw *hw, const struct adc_conf *info)
{
	int err;
	u32 data, ctl;

	/*  Set ADC reset bit as output */
	data = hw_read_20kx(hw, GPIO_CTRL);
	data |= (0x1 << 15);
	hw_write_20kx(hw, GPIO_CTRL, data);

	/* Initialize I2C */
	err = hw20k2_i2c_init(hw, 0x1A, 1, 1);
	if (err < 0) {
		dev_alert(hw->card->dev, "Failure to acquire I2C!!!\n");
		goto error;
	}

	/* Reset the ADC (reset is active low). */
	data = hw_read_20kx(hw, GPIO_DATA);
	data &= ~(0x1 << 15);
	hw_write_20kx(hw, GPIO_DATA, data);

	if (hw->model == CTSB1270) {
		/* Set up the PCM4220 ADC on Titanium HD */
		data &= ~0x0C;
		if (1 == info->msr)
			data |= 0x00; /* Single Speed Mode 32-50kHz */
		else if (2 == info->msr)
			data |= 0x08; /* Double Speed Mode 50-108kHz */
		else
			data |= 0x04; /* Quad Speed Mode 108kHz-216kHz */
		hw_write_20kx(hw, GPIO_DATA, data);
	}

	usleep_range(10000, 11000);
	/* Return the ADC to normal operation. */
	data |= (0x1 << 15);
	hw_write_20kx(hw, GPIO_DATA, data);
	msleep(50);

	/* I2C write to register offset 0x0B to set ADC LRCLK polarity */
	/* invert bit, interface format to I2S, word length to 24-bit, */
	/* enable ADC high pass filter. Fixes bug 5323?		*/
	hw20k2_i2c_write(hw, MAKE_WM8775_ADDR(WM8775_IC, 0x26),
			 MAKE_WM8775_DATA(0x26));

	/* Set the master mode (256fs) */
	if (1 == info->msr) {
		/* slave mode, 128x oversampling 256fs */
		hw20k2_i2c_write(hw, MAKE_WM8775_ADDR(WM8775_MMC, 0x02),
						MAKE_WM8775_DATA(0x02));
	} else if ((2 == info->msr) || (4 == info->msr)) {
		/* slave mode, 64x oversampling, 256fs */
		hw20k2_i2c_write(hw, MAKE_WM8775_ADDR(WM8775_MMC, 0x0A),
						MAKE_WM8775_DATA(0x0A));
	} else {
		dev_alert(hw->card->dev,
			  "Invalid master sampling rate (msr %d)!!!\n",
			  info->msr);
		err = -EINVAL;
		goto error;
	}

	if (hw->model != CTSB1270) {
		/* Configure GPIO bit 14 change to line-in/mic-in */
		ctl = hw_read_20kx(hw, GPIO_CTRL);
		ctl |= 0x1 << 14;
		hw_write_20kx(hw, GPIO_CTRL, ctl);
		hw_adc_input_select(hw, ADC_LINEIN);
	} else {
		hw_wm8775_input_select(hw, 0, 0);
	}

	return 0;
error:
	hw20k2_i2c_uninit(hw);
	return err;
}