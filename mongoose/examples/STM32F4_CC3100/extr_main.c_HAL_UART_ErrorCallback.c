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
typedef  int /*<<< orphan*/  UART_HandleTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  BSP_LED_On (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LED4 ; 

void HAL_UART_ErrorCallback(UART_HandleTypeDef *UartHandle) {
  /* Turn LED4 (red) on: Transfer error in reception/transmission process */
  BSP_LED_On(LED4);
}