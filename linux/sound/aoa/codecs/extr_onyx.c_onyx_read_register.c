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
typedef  scalar_t__ u8 ;
struct onyx {scalar_t__* cache; int /*<<< orphan*/  i2c; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ FIRSTREGISTER ; 
 scalar_t__ ONYX_REG_CONTROL ; 
 scalar_t__ i2c_smbus_read_byte_data (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int onyx_read_register(struct onyx *onyx, u8 reg, u8 *value)
{
	s32 v;

	if (reg != ONYX_REG_CONTROL) {
		*value = onyx->cache[reg-FIRSTREGISTER];
		return 0;
	}
	v = i2c_smbus_read_byte_data(onyx->i2c, reg);
	if (v < 0) {
		*value = 0;
		return -1;
	}
	*value = (u8)v;
	onyx->cache[ONYX_REG_CONTROL-FIRSTREGISTER] = *value;
	return 0;
}