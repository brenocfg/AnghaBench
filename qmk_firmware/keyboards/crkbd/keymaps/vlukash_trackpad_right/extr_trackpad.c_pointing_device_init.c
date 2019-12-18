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
 int /*<<< orphan*/  LVL_SHIFT_EN_HI ; 
 int /*<<< orphan*/  LVL_SHIFT_EN_INIT ; 
 int /*<<< orphan*/  LVL_SHIFT_EN_LO ; 
 int /*<<< orphan*/  SPI_Init (int) ; 
 int SPI_MODE_MASTER ; 
 int SPI_SPEED_FCPU_DIV_8 ; 
 int /*<<< orphan*/  TP_CS_HI ; 
 int /*<<< orphan*/  TP_CS_INIT ; 
 int /*<<< orphan*/  TP_RESET_HI ; 
 int /*<<< orphan*/  TP_RESET_INIT ; 
 int /*<<< orphan*/  TP_RESET_LO ; 
 int /*<<< orphan*/  TP_SHUTDOWN_INIT ; 
 int /*<<< orphan*/  TP_SHUTDOWN_LO ; 
 int /*<<< orphan*/  wait_ms (int) ; 

void pointing_device_init(void){

  SPI_Init(SPI_SPEED_FCPU_DIV_8 | SPI_MODE_MASTER);

  // Set as output
  TP_RESET_INIT;
  TP_SHUTDOWN_INIT;
  TP_CS_INIT;
  LVL_SHIFT_EN_INIT;

  // Reset level shifter
  LVL_SHIFT_EN_LO;
  wait_ms(100);
  LVL_SHIFT_EN_HI;

  // Force a BB-8520 reset
  TP_RESET_HI;
  wait_ms(100);
  TP_RESET_LO;

  // Turn on BB-8520 trackpad
  TP_SHUTDOWN_LO;

  TP_CS_HI;
}