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
 int /*<<< orphan*/  ADCCHAN_ACCEL0 ; 
 int /*<<< orphan*/  ADCCHAN_ACCEL1 ; 
 int /*<<< orphan*/  MAX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ NO_FAULT ; 
 int /*<<< orphan*/  adc_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dac_set (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gas_set_0 ; 
 int /*<<< orphan*/  gas_set_1 ; 
 int /*<<< orphan*/  pdl0 ; 
 int /*<<< orphan*/  pdl1 ; 
 scalar_t__ state ; 
 int /*<<< orphan*/  watchdog_feed () ; 

void pedal(void) {
  // read/write
  pdl0 = adc_get(ADCCHAN_ACCEL0);
  pdl1 = adc_get(ADCCHAN_ACCEL1);

  // write the pedal to the DAC
  if (state == NO_FAULT) {
    dac_set(0, MAX(gas_set_0, pdl0));
    dac_set(1, MAX(gas_set_1, pdl1));
  } else {
    dac_set(0, pdl0);
    dac_set(1, pdl1);
  }

  watchdog_feed();
}