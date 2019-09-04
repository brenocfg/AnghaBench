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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  hmc5883_i2c_id ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int r8u (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  w8u (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int hmc5883_setup(lua_State* L) {
    uint8_t  devid_a, devid_b, devid_c;

    devid_a = r8u(hmc5883_i2c_id, 10);
    devid_b = r8u(hmc5883_i2c_id, 11);
    devid_c = r8u(hmc5883_i2c_id, 12);

    if ((devid_a != 0x48) || (devid_b != 0x34) || (devid_c != 0x33)) {
        return luaL_error(L, "device not found");
    }

    // 8 sample average, 15 Hz update rate, normal measurement
    w8u(hmc5883_i2c_id, 0x00, 0x70);

    // Gain = 5
    w8u(hmc5883_i2c_id, 0x01, 0xA0);

    // Continuous measurement
    w8u(hmc5883_i2c_id, 0x02, 0x00);

    return 0;
}