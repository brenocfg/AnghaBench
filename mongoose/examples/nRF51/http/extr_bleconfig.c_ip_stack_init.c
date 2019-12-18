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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  APP_ERROR_CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lwip_init () ; 
 int /*<<< orphan*/  nrf51_driver_init () ; 
 int /*<<< orphan*/  nrf51_sdk_mem_init () ; 

__attribute__((used)) static void ip_stack_init(void)
{
  uint32_t err_code = nrf51_sdk_mem_init();
  APP_ERROR_CHECK(err_code);

  //Initialize LwIP stack.
  lwip_init();

  //Initialize LwIP stack driver.
  err_code = nrf51_driver_init();
  APP_ERROR_CHECK(err_code);
}