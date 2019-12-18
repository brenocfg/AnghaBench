#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_4__ {TYPE_1__* harness_config; } ;
struct TYPE_3__ {int /*<<< orphan*/  adc_channel_SBU2; int /*<<< orphan*/  adc_channel_SBU1; } ;

/* Variables and functions */
 scalar_t__ HARNESS_CONNECTED_THRESHOLD ; 
 int /*<<< orphan*/  HARNESS_STATUS_FLIPPED ; 
 int /*<<< orphan*/  HARNESS_STATUS_NC ; 
 int /*<<< orphan*/  HARNESS_STATUS_NORMAL ; 
 scalar_t__ adc_get (int /*<<< orphan*/ ) ; 
 TYPE_2__* current_board ; 

uint8_t harness_detect_orientation(void) {
  uint8_t ret = HARNESS_STATUS_NC;

  #ifndef BOOTSTUB
  uint32_t sbu1_voltage = adc_get(current_board->harness_config->adc_channel_SBU1);
  uint32_t sbu2_voltage = adc_get(current_board->harness_config->adc_channel_SBU2);

  // Detect connection and orientation
  if((sbu1_voltage < HARNESS_CONNECTED_THRESHOLD) || (sbu2_voltage < HARNESS_CONNECTED_THRESHOLD)){
    if (sbu1_voltage < sbu2_voltage) {
      // orientation normal
      ret = HARNESS_STATUS_NORMAL;
    } else {
      // orientation flipped
      ret = HARNESS_STATUS_FLIPPED;
    }
  }
  #endif

  return ret;
}