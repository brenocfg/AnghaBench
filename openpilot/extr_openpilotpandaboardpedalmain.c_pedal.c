#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int KR; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADCCHAN_ACCEL0 ; 
 int /*<<< orphan*/  ADCCHAN_ACCEL1 ; 
 TYPE_1__* IWDG ; 
 scalar_t__ NO_FAULT ; 
 int /*<<< orphan*/  adc_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dac_set (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gas_set_0 ; 
 int /*<<< orphan*/  gas_set_1 ; 
 int /*<<< orphan*/  max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdl0 ; 
 int /*<<< orphan*/  pdl1 ; 
 scalar_t__ state ; 

void pedal() {
  // read/write
  pdl0 = adc_get(ADCCHAN_ACCEL0);
  pdl1 = adc_get(ADCCHAN_ACCEL1);

  // write the pedal to the DAC
  if (state == NO_FAULT) {
    dac_set(0, max(gas_set_0, pdl0));
    dac_set(1, max(gas_set_1, pdl1));
  } else {
    dac_set(0, pdl0);
    dac_set(1, pdl1);
  }

  // feed the watchdog
  IWDG->KR = 0xAAAA;
}