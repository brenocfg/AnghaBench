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
typedef  int u32 ;
struct ufx_data {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  check_warn_return (int,char*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  pr_warn (char*,...) ; 
 int ufx_reg_read (struct ufx_data*,int,int*) ; 
 int ufx_reg_write (struct ufx_data*,int,int) ; 

__attribute__((used)) static int ufx_i2c_wait_busy(struct ufx_data *dev)
{
	u32 tmp;
	int i, status;

	for (i = 0; i < 15; i++) {
		status = ufx_reg_read(dev, 0x1100, &tmp);
		check_warn_return(status, "0x1100 read failed");

		/* if BUSY is clear, check for error */
		if ((tmp & 0x80000000) == 0) {
			if (tmp & 0x20000000) {
				pr_warn("I2C read failed, 0x1100=0x%08x", tmp);
				return -EIO;
			}

			return 0;
		}

		/* perform the first 10 retries without delay */
		if (i >= 10)
			msleep(10);
	}

	pr_warn("I2C access timed out, resetting I2C hardware");
	status =  ufx_reg_write(dev, 0x1100, 0x40000000);
	check_warn_return(status, "0x1100 write failed");

	return -ETIMEDOUT;
}