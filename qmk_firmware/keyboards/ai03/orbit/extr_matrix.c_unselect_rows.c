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
typedef  size_t uint8_t ;

/* Variables and functions */
 size_t ROWS_PER_HAND ; 
 int /*<<< orphan*/ * row_pins ; 
 int /*<<< orphan*/  setPinInputHigh (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void unselect_rows(void) {
  for (uint8_t x = 0; x < ROWS_PER_HAND; x++) {
    setPinInputHigh(row_pins[x]);
  }
}