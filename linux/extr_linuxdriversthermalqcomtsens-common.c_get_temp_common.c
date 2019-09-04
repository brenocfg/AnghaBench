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
struct tsens_sensor {unsigned int hw_id; } ;
struct tsens_device {int /*<<< orphan*/  map; struct tsens_sensor* sensor; } ;

/* Variables and functions */
 unsigned int S0_ST_ADDR ; 
 unsigned int SN_ADDR_OFFSET ; 
 int SN_ST_TEMP_MASK ; 
 int code_to_degc (int,struct tsens_sensor*) ; 
 int regmap_read (int /*<<< orphan*/ ,unsigned int,int*) ; 

int get_temp_common(struct tsens_device *tmdev, int id, int *temp)
{
	struct tsens_sensor *s = &tmdev->sensor[id];
	u32 code;
	unsigned int status_reg;
	int last_temp = 0, ret;

	status_reg = S0_ST_ADDR + s->hw_id * SN_ADDR_OFFSET;
	ret = regmap_read(tmdev->map, status_reg, &code);
	if (ret)
		return ret;
	last_temp = code & SN_ST_TEMP_MASK;

	*temp = code_to_degc(last_temp, s) * 1000;

	return 0;
}