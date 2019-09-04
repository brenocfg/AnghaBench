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
struct tsens_sensor {int hw_id; } ;
struct tsens_device {int tm_offset; int /*<<< orphan*/  map; struct tsens_sensor* sensor; } ;

/* Variables and functions */
 int LAST_TEMP_MASK ; 
 int STATUS_OFFSET ; 
 int STATUS_VALID_BIT ; 
 scalar_t__ fls (int) ; 
 int regmap_read (int /*<<< orphan*/ ,unsigned int,int*) ; 
 int sign_extend32 (int,scalar_t__) ; 

__attribute__((used)) static int get_temp_tsens_v2(struct tsens_device *tmdev, int id, int *temp)
{
	struct tsens_sensor *s = &tmdev->sensor[id];
	u32 code;
	unsigned int status_reg;
	u32 last_temp = 0, last_temp2 = 0, last_temp3 = 0;
	int ret;

	status_reg = tmdev->tm_offset + STATUS_OFFSET + s->hw_id * 4;
	ret = regmap_read(tmdev->map, status_reg, &code);
	if (ret)
		return ret;
	last_temp = code & LAST_TEMP_MASK;
	if (code & STATUS_VALID_BIT)
		goto done;

	/* Try a second time */
	ret = regmap_read(tmdev->map, status_reg, &code);
	if (ret)
		return ret;
	if (code & STATUS_VALID_BIT) {
		last_temp = code & LAST_TEMP_MASK;
		goto done;
	} else {
		last_temp2 = code & LAST_TEMP_MASK;
	}

	/* Try a third/last time */
	ret = regmap_read(tmdev->map, status_reg, &code);
	if (ret)
		return ret;
	if (code & STATUS_VALID_BIT) {
		last_temp = code & LAST_TEMP_MASK;
		goto done;
	} else {
		last_temp3 = code & LAST_TEMP_MASK;
	}

	if (last_temp == last_temp2)
		last_temp = last_temp2;
	else if (last_temp2 == last_temp3)
		last_temp = last_temp3;
done:
	/* Convert temperature from deciCelsius to milliCelsius */
	*temp = sign_extend32(last_temp, fls(LAST_TEMP_MASK) - 1) * 100;

	return 0;
}