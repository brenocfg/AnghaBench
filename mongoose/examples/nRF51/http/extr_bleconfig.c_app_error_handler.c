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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  ALL_APP_LED ; 
 int /*<<< orphan*/  APPL_LOG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  LEDS_ON (int /*<<< orphan*/ ) ; 

void app_error_handler(uint32_t error_code, uint32_t line_num, const uint8_t * p_file_name)
{
  //Halt the application and notify of error using the LEDs.
  APPL_LOG("[** ASSERT **]: Error 0x%08lX, Line %ld, File %s\r\n",error_code, line_num, p_file_name);
  LEDS_ON(ALL_APP_LED);
  for(;;)
  {
  }

  // @note: In case on assert, it is desired to only recover and reset, uncomment the line below.
  //NVIC_SystemReset();
}