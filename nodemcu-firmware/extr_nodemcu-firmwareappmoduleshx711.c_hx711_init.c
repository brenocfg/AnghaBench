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
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  MOD_CHECK_ID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLATFORM_GPIO_FLOAT ; 
 int /*<<< orphan*/  PLATFORM_GPIO_INPUT ; 
 int /*<<< orphan*/  PLATFORM_GPIO_OUTPUT ; 
 int /*<<< orphan*/  clk_pin ; 
 int /*<<< orphan*/  data_pin ; 
 int /*<<< orphan*/  gpio ; 
 int /*<<< orphan*/  luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  platform_gpio_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_gpio_write (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hx711_init(lua_State* L) {
  clk_pin = luaL_checkinteger(L,1);
  data_pin = luaL_checkinteger(L,2);
  MOD_CHECK_ID( gpio, clk_pin );
  MOD_CHECK_ID( gpio, data_pin );

  platform_gpio_mode(clk_pin, PLATFORM_GPIO_OUTPUT, PLATFORM_GPIO_FLOAT);
  platform_gpio_mode(data_pin, PLATFORM_GPIO_INPUT, PLATFORM_GPIO_FLOAT);
  platform_gpio_write(clk_pin,1);//put chip to sleep.
  return 0;
}