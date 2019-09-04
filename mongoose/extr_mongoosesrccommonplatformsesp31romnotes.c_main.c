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
typedef  int uint32_t ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  CLEAR_PERI_REG_MASK (scalar_t__,int) ; 
 int GET_PERI_REG_BITS (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GPIO_STRAP ; 
 scalar_t__ RTC ; 
 int /*<<< orphan*/  SET_PERI_REG_MASK (scalar_t__,int) ; 
 int _X_get_rst_cause () ; 
 int /*<<< orphan*/  _X_uart_attach () ; 
 int /*<<< orphan*/  _X_uart_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  boot_banner ; 
 int /*<<< orphan*/  ets_printf (char*,char*,int,...) ; 
 int /*<<< orphan*/  fw_build ; 

void main(void) {
  uint32_t rst_cause = _X_get_rst_cause();
  CLEAR_PERI_REG_MASK(RTC+0x80, BIT(17));     // a
  SET_PERI_REG_MASK(RTC+0x80, BIT(12));       // b
  uint32_t boot_mode = GET_PERI_REG_BITS(GPIO_STRAP, 6, 0);  // c
  if (boot_mode & (BIT(5) | BIT(4)) == (BIT(5) | BIT(4)) || boot_mode == 24 || boot_mode == 26) {
    CLEAR_PERI_REG_MASK(RTC+0x74, 0xff);
  }
  if (boot_mode & (BIT(5) | BIT(4)) == BIT(5)) {
    CLEAR_PERI_REG_MASK(RTC+0x94, BIT(31));
    CLEAR_PERI_REG_MASK(RTC+0x98, BIT(31));
    CLEAR_PERI_REG_MASK(RTC+0x9c, BIT(31));
    CLEAR_PERI_REG_MASK(RTC+0xa0, BIT(31));
    CLEAR_PERI_REG_MASK(RTC+0xa4, BIT(31));
    CLEAR_PERI_REG_MASK(RTC+0xa8, BIT(31));
    CLEAR_PERI_REG_MASK(RTC+0xac, BIT(31));
  }
  if (boot_mode & (BIT(5) | BIT(3)) == 0) {
    // ... 1405
  }
  CLEAR_PERI_REG_MASK(RTC+0x74, 0xff);
  _X_uart_attach();
  _X_uart_init(0);
  // GPIO_STRAP ...
  ets_printf(boot_banner, fw_build, rst_cause, boot_mode);
  // rst_cause
  if (rst_cause == 1 || rst_cause == 2) {
    
  } else {
    // ...
  }
  ets_printf("%s %u", "ets_main.c", 305);
  while(1) {}
}