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

/* Variables and functions */
 int /*<<< orphan*/  PLATFORM_GPIO_HIGH ; 
 int /*<<< orphan*/  m_spi_no ; 
 int /*<<< orphan*/  m_ss_pin ; 
 int /*<<< orphan*/  platform_gpio_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_spi_send_recv (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void sdcard_chipselect_high( void ) {
  platform_gpio_write( m_ss_pin, PLATFORM_GPIO_HIGH );
  // send some cc to ensure that MISO returns to high
  platform_spi_send_recv( m_spi_no, 8, 0xff );
}