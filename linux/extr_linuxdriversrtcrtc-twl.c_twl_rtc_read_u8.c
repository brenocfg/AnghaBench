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
typedef  size_t u8 ;
struct twl_rtc {int /*<<< orphan*/ * reg_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  TWL_MODULE_RTC ; 
 int /*<<< orphan*/  pr_err (char*,size_t,int) ; 
 int twl_i2c_read_u8 (int /*<<< orphan*/ ,size_t*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int twl_rtc_read_u8(struct twl_rtc *twl_rtc, u8 *data, u8 reg)
{
	int ret;

	ret = twl_i2c_read_u8(TWL_MODULE_RTC, data, (twl_rtc->reg_map[reg]));
	if (ret < 0)
		pr_err("Could not read TWL register %X - error %d\n", reg, ret);
	return ret;
}