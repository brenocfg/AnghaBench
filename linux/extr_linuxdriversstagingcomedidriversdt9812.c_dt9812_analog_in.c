#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u8 ;
typedef  int u16 ;
struct dt9812_rmw_byte {int address; int and_mask; int or_value; } ;
struct dt9812_private {int device; int /*<<< orphan*/  mut; } ;
struct comedi_device {struct dt9812_private* private; } ;
typedef  enum dt9812_gain { ____Placeholder_dt9812_gain } dt9812_gain ;

/* Variables and functions */
#define  DT9812_DEVID_DT9812_10 129 
#define  DT9812_DEVID_DT9812_2PT5 128 
 int F020_MASK_ADC0CN_AD0BUSY ; 
 int F020_MASK_ADC0CN_AD0EN ; 
 int F020_MASK_ADC0CN_AD0INT ; 
 int F020_SFR_ADC0CN ; 
 int F020_SFR_ADC0H ; 
 int F020_SFR_ADC0L ; 
 int /*<<< orphan*/  dt9812_configure_gain (struct comedi_device*,struct dt9812_rmw_byte*,int) ; 
 int /*<<< orphan*/  dt9812_configure_mux (struct comedi_device*,struct dt9812_rmw_byte*,int) ; 
 int dt9812_read_multiple_registers (struct comedi_device*,int,int*,int*) ; 
 int dt9812_rmw_multiple_registers (struct comedi_device*,int,struct dt9812_rmw_byte*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dt9812_analog_in(struct comedi_device *dev,
			    int channel, u16 *value, enum dt9812_gain gain)
{
	struct dt9812_private *devpriv = dev->private;
	struct dt9812_rmw_byte rmw[3];
	u8 reg[3] = {
		F020_SFR_ADC0CN,
		F020_SFR_ADC0H,
		F020_SFR_ADC0L
	};
	u8 val[3];
	int ret;

	mutex_lock(&devpriv->mut);

	/* 1 select the gain */
	dt9812_configure_gain(dev, &rmw[0], gain);

	/* 2 set the MUX to select the channel */
	dt9812_configure_mux(dev, &rmw[1], channel);

	/* 3 start conversion */
	rmw[2].address = F020_SFR_ADC0CN;
	rmw[2].and_mask = 0xff;
	rmw[2].or_value = F020_MASK_ADC0CN_AD0EN | F020_MASK_ADC0CN_AD0BUSY;

	ret = dt9812_rmw_multiple_registers(dev, 3, rmw);
	if (ret)
		goto exit;

	/* read the status and ADC */
	ret = dt9812_read_multiple_registers(dev, 3, reg, val);
	if (ret)
		goto exit;

	/*
	 * An ADC conversion takes 16 SAR clocks cycles, i.e. about 9us.
	 * Therefore, between the instant that AD0BUSY was set via
	 * dt9812_rmw_multiple_registers and the read of AD0BUSY via
	 * dt9812_read_multiple_registers, the conversion should be complete
	 * since these two operations require two USB transactions each taking
	 * at least a millisecond to complete.  However, lets make sure that
	 * conversion is finished.
	 */
	if ((val[0] & (F020_MASK_ADC0CN_AD0INT | F020_MASK_ADC0CN_AD0BUSY)) ==
	    F020_MASK_ADC0CN_AD0INT) {
		switch (devpriv->device) {
		case DT9812_DEVID_DT9812_10:
			/*
			 * For DT9812-10V the personality module set the
			 * encoding to 2's complement. Hence, convert it before
			 * returning it
			 */
			*value = ((val[1] << 8) | val[2]) + 0x800;
			break;
		case DT9812_DEVID_DT9812_2PT5:
			*value = (val[1] << 8) | val[2];
			break;
		}
	}

exit:
	mutex_unlock(&devpriv->mut);

	return ret;
}