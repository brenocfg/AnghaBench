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
 int /*<<< orphan*/  BIT2 ; 
 int /*<<< orphan*/  FUNC_U1TXD_BK ; 
 int /*<<< orphan*/  GPIO_ENABLE_W1TC_ADDRESS ; 
 int /*<<< orphan*/  GPIO_REG_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int const MODE_DUAL ; 
 int const MODE_SINGLE ; 
 int /*<<< orphan*/  PERIPHS_IO_MUX_GPIO2_U ; 
 int /*<<< orphan*/  PIN_FUNC_SELECT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLATFORM_GPIO_FLOAT ; 
 int /*<<< orphan*/  PLATFORM_GPIO_OUTPUT ; 
 int UART_BIT_NUM_S ; 
 int /*<<< orphan*/  UART_CLKDIV (int) ; 
 int UART_CLK_FREQ ; 
 int /*<<< orphan*/  UART_CONF0 (int) ; 
 int UART_STOP_BIT_NUM_S ; 
 int UART_TXD_INV ; 
 int /*<<< orphan*/  WRITE_PERI_REG (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  luaL_argcheck (int /*<<< orphan*/ *,int,int,char*) ; 
 int luaL_optinteger (int /*<<< orphan*/ *,int,int const) ; 
 int /*<<< orphan*/  os_delay_us (int) ; 
 int /*<<< orphan*/  platform_gpio_mode (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_gpio_write (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ws2812_init(lua_State* L) {
  const int mode = luaL_optinteger(L, 1, MODE_SINGLE);
  luaL_argcheck(L, mode == MODE_SINGLE || mode == MODE_DUAL, 1, "ws2812.SINGLE or ws2812.DUAL expected");

  // Configure UART1
  // Set baudrate of UART1 to 3200000
  WRITE_PERI_REG(UART_CLKDIV(1), UART_CLK_FREQ / 3200000);
  // Set UART Configuration No parity / 6 DataBits / 1 StopBits / Invert TX
  WRITE_PERI_REG(UART_CONF0(1), UART_TXD_INV | (1 << UART_STOP_BIT_NUM_S) | (1 << UART_BIT_NUM_S));

  if (mode == MODE_DUAL) {
    // Configure UART0
    // Set baudrate of UART0 to 3200000
    WRITE_PERI_REG(UART_CLKDIV(0), UART_CLK_FREQ / 3200000);
    // Set UART Configuration No parity / 6 DataBits / 1 StopBits / Invert TX
    WRITE_PERI_REG(UART_CONF0(0), UART_TXD_INV | (1 << UART_STOP_BIT_NUM_S) | (1 << UART_BIT_NUM_S));
  }

  // Pull GPIO2 down
  platform_gpio_mode(4, PLATFORM_GPIO_OUTPUT, PLATFORM_GPIO_FLOAT);
  platform_gpio_write(4, 0);

  // Waits 10us to simulate a reset
  os_delay_us(10);

  // Redirect UART1 to GPIO2
  // Disable GPIO2
  GPIO_REG_WRITE(GPIO_ENABLE_W1TC_ADDRESS, BIT2);
  // Enable Function 2 for GPIO2 (U1TXD)
  PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO2_U, FUNC_U1TXD_BK);

  return 0;
}