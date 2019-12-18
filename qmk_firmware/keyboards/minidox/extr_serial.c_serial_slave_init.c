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
 int EICRA ; 
 int EIMSK ; 
 int /*<<< orphan*/  INT0 ; 
 int /*<<< orphan*/  ISC00 ; 
 int /*<<< orphan*/  ISC01 ; 
 int _BV (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serial_input () ; 

void serial_slave_init(void) {
  serial_input();

  // Enable INT0
  EIMSK |= _BV(INT0);
  // Trigger on falling edge of INT0
  EICRA &= ~(_BV(ISC00) | _BV(ISC01));
}