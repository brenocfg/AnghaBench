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
 int /*<<< orphan*/  DDRB ; 
 int /*<<< orphan*/  DDRC ; 
 int /*<<< orphan*/  PB0 ; 
 int /*<<< orphan*/  PC7 ; 
 int /*<<< orphan*/  _BV (int /*<<< orphan*/ ) ; 

void matrix_init_user(void) {
  DDRB |= _BV(PB0);
  DDRC |= _BV(PC7);
}