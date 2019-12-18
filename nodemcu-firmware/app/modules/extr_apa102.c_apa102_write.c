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
typedef  size_t uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_OUTPUT_SET (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MOD_CHECK_ID (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  PLATFORM_GPIO_FLOAT ; 
 int /*<<< orphan*/  PLATFORM_GPIO_HIGH ; 
 int /*<<< orphan*/  PLATFORM_GPIO_LOW ; 
 int /*<<< orphan*/  PLATFORM_GPIO_OUTPUT ; 
 int /*<<< orphan*/  apa102_send_buffer (int,int,int*,int) ; 
 int /*<<< orphan*/  gpio ; 
 size_t luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 char* luaL_checklstring (int /*<<< orphan*/ *,int,size_t*) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int* pin_num ; 
 int /*<<< orphan*/  platform_gpio_mode (size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int apa102_write(lua_State* L) {
  uint8_t data_pin = luaL_checkinteger(L, 1);
  MOD_CHECK_ID(gpio, data_pin);
  uint32_t alt_data_pin = pin_num[data_pin];

  uint8_t clock_pin = luaL_checkinteger(L, 2);
  MOD_CHECK_ID(gpio, clock_pin);
  uint32_t alt_clock_pin = pin_num[clock_pin];

  size_t buf_len;
  const char *buf = luaL_checklstring(L, 3, &buf_len);
  uint32_t nbr_frames = buf_len / 4;

  if (nbr_frames > 100000) {
    return luaL_error(L, "The supplied buffer is too long, and might cause the callback watchdog to bark.");
  }

  // Initialize the output pins
  platform_gpio_mode(data_pin, PLATFORM_GPIO_OUTPUT, PLATFORM_GPIO_FLOAT);
  GPIO_OUTPUT_SET(alt_data_pin, PLATFORM_GPIO_HIGH); // Set pin high
  platform_gpio_mode(clock_pin, PLATFORM_GPIO_OUTPUT, PLATFORM_GPIO_FLOAT);
  GPIO_OUTPUT_SET(alt_clock_pin, PLATFORM_GPIO_LOW); // Set pin low

  // Send the buffers
  apa102_send_buffer(alt_data_pin, alt_clock_pin, (uint32_t *) buf, (uint32_t) nbr_frames);
  return 0;
}