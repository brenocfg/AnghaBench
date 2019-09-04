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
typedef  int u8 ;
struct ds278x_info {TYPE_1__* client; } ;
typedef  int s16 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DS2782_CURRENT_UNITS ; 
 int /*<<< orphan*/  DS2782_REG_RSNSP ; 
 int /*<<< orphan*/  DS278x_REG_CURRENT_MSB ; 
 int ENXIO ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int ds278x_read_reg (struct ds278x_info*,int /*<<< orphan*/ ,int*) ; 
 int ds278x_read_reg16 (struct ds278x_info*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int ds2782_get_current(struct ds278x_info *info, int *current_uA)
{
	int sense_res;
	int err;
	u8 sense_res_raw;
	s16 raw;

	/*
	 * The units of measurement for current are dependent on the value of
	 * the sense resistor.
	 */
	err = ds278x_read_reg(info, DS2782_REG_RSNSP, &sense_res_raw);
	if (err)
		return err;
	if (sense_res_raw == 0) {
		dev_err(&info->client->dev, "sense resistor value is 0\n");
		return -ENXIO;
	}
	sense_res = 1000 / sense_res_raw;

	dev_dbg(&info->client->dev, "sense resistor = %d milli-ohms\n",
		sense_res);
	err = ds278x_read_reg16(info, DS278x_REG_CURRENT_MSB, &raw);
	if (err)
		return err;
	*current_uA = raw * (DS2782_CURRENT_UNITS / sense_res);
	return 0;
}