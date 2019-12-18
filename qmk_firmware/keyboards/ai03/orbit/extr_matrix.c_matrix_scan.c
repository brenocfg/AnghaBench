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
typedef  scalar_t__ uint8_t ;

/* Variables and functions */
 scalar_t__ ERROR_DISCONNECT_COUNT ; 
 int ROWS_PER_HAND ; 
 scalar_t__ _matrix_scan () ; 
 scalar_t__ is_keyboard_master () ; 
 scalar_t__* matrix ; 
 int /*<<< orphan*/  matrix_scan_quantum () ; 
 int /*<<< orphan*/  matrix_slave_scan_user () ; 
 int thatHand ; 
 int thisHand ; 
 int /*<<< orphan*/  transport_master (scalar_t__*) ; 
 int /*<<< orphan*/  transport_slave (scalar_t__*) ; 

uint8_t matrix_scan(void) {
  uint8_t ret = _matrix_scan();

  if (is_keyboard_master()) {
    static uint8_t error_count;

    if (!transport_master(matrix + thatHand)) {
      error_count++;

      if (error_count > ERROR_DISCONNECT_COUNT) {
        // reset other half if disconnected
        for (int i = 0; i < ROWS_PER_HAND; ++i) {
          matrix[thatHand + i] = 0;
        }
      }
    } else {
      error_count = 0;
    }

    matrix_scan_quantum();
  } else {
    transport_slave(matrix + thisHand);
    matrix_slave_scan_user();
  }

  return ret;
}