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
typedef  int u32 ;
typedef  int u16 ;
struct db2k_private {scalar_t__ plx; } ;
struct comedi_device {scalar_t__ mmio; int /*<<< orphan*/  class_dev; struct db2k_private* private; } ;

/* Variables and functions */
 int DB2K_CPLD_VERSION_MASK ; 
 int DB2K_CPLD_VERSION_NEW ; 
 scalar_t__ DB2K_REG_CPLD_STATUS ; 
 int EINVAL ; 
 int EIO ; 
 int PLX_CNTRL_EEPRESENT ; 
 scalar_t__ PLX_REG_CNTRL ; 
 int /*<<< orphan*/  db2k_pulse_prog_pin (struct comedi_device*) ; 
 int /*<<< orphan*/  db2k_reload_plx (struct comedi_device*) ; 
 int /*<<< orphan*/  db2k_reset_local_bus (struct comedi_device*) ; 
 int db2k_wait_cpld_init (struct comedi_device*) ; 
 int db2k_wait_fpga_programmed (struct comedi_device*) ; 
 int db2k_write_cpld (struct comedi_device*,int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int readl (scalar_t__) ; 
 int readw (scalar_t__) ; 

__attribute__((used)) static int db2k_load_firmware(struct comedi_device *dev, const u8 *cpld_array,
			      size_t len, unsigned long context)
{
	struct db2k_private *devpriv = dev->private;
	int result = -EIO;
	u32 cntrl;
	int retry;
	size_t i;
	bool new_cpld;

	/* Look for FPGA start sequence in firmware. */
	for (i = 0; i + 1 < len; i++) {
		if (cpld_array[i] == 0xff && cpld_array[i + 1] == 0x20)
			break;
	}
	if (i + 1 >= len) {
		dev_err(dev->class_dev, "bad firmware - no start sequence\n");
		return -EINVAL;
	}
	/* Check length is even. */
	if ((len - i) & 1) {
		dev_err(dev->class_dev,
			"bad firmware - odd length (%zu = %zu - %zu)\n",
			len - i, len, i);
		return -EINVAL;
	}
	/* Strip firmware header. */
	cpld_array += i;
	len -= i;

	/* Check to make sure the serial eeprom is present on the board */
	cntrl = readl(devpriv->plx + PLX_REG_CNTRL);
	if (!(cntrl & PLX_CNTRL_EEPRESENT))
		return -EIO;

	for (retry = 0; retry < 3; retry++) {
		db2k_reset_local_bus(dev);
		db2k_reload_plx(dev);
		db2k_pulse_prog_pin(dev);
		result = db2k_wait_cpld_init(dev);
		if (result)
			continue;

		new_cpld = (readw(dev->mmio + DB2K_REG_CPLD_STATUS) &
			    DB2K_CPLD_VERSION_MASK) == DB2K_CPLD_VERSION_NEW;
		for (; i < len; i += 2) {
			u16 data = (cpld_array[i] << 8) + cpld_array[i + 1];

			result = db2k_write_cpld(dev, data, new_cpld);
			if (result)
				break;
		}
		if (result == 0)
			result = db2k_wait_fpga_programmed(dev);
		if (result == 0) {
			db2k_reset_local_bus(dev);
			db2k_reload_plx(dev);
			break;
		}
	}
	return result;
}