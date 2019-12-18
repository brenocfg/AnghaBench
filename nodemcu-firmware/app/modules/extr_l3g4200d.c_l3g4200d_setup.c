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
 int /*<<< orphan*/  i2c_id ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int r8u (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  w8u (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int l3g4200d_setup(lua_State* L) {
    uint8_t  devid;

    devid = r8u(i2c_id, 0xF);

    if (devid != 0xD3) {
        return luaL_error(L, "device not found");
    }

    w8u(i2c_id, 0x20, 0xF);

    return 0;
}