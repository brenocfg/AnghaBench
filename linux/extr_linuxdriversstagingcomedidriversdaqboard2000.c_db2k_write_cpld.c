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
typedef  int /*<<< orphan*/  u16 ;
struct comedi_device {scalar_t__ mmio; } ;

/* Variables and functions */
 int DB2K_CPLD_STATUS_INIT ; 
 scalar_t__ DB2K_REG_CPLD_STATUS ; 
 scalar_t__ DB2K_REG_CPLD_WDATA ; 
 int EIO ; 
 int db2k_wait_cpld_txready (struct comedi_device*) ; 
 int readw (scalar_t__) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  writew (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int db2k_write_cpld(struct comedi_device *dev, u16 data, bool new_cpld)
{
	int result = 0;

	if (new_cpld) {
		result = db2k_wait_cpld_txready(dev);
		if (result)
			return result;
	} else {
		usleep_range(10, 20);
	}
	writew(data, dev->mmio + DB2K_REG_CPLD_WDATA);
	if (!(readw(dev->mmio + DB2K_REG_CPLD_STATUS) & DB2K_CPLD_STATUS_INIT))
		result = -EIO;

	return result;
}