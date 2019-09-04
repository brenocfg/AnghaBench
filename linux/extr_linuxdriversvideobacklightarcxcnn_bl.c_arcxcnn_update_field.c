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
struct arcxcnn {int /*<<< orphan*/  client; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int i2c_smbus_read_byte_data (int /*<<< orphan*/ ,int) ; 
 int i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int arcxcnn_update_field(struct arcxcnn *lp, u8 reg, u8 mask, u8 data)
{
	int ret;
	u8 tmp;

	ret = i2c_smbus_read_byte_data(lp->client, reg);
	if (ret < 0) {
		dev_err(lp->dev, "failed to read 0x%.2x\n", reg);
		return ret;
	}

	tmp = (u8)ret;
	tmp &= ~mask;
	tmp |= data & mask;

	return i2c_smbus_write_byte_data(lp->client, reg, tmp);
}