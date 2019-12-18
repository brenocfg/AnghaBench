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
 size_t MATRIX_ROWS ; 
 int PORTB ; 
 int PORTD ; 
 int /*<<< orphan*/  TX_RX_LED_INIT ; 
 int debug_enable ; 
 int debug_matrix ; 
 int debug_mouse ; 
 int /*<<< orphan*/  has_usb () ; 
 int /*<<< orphan*/  init_cols () ; 
 int /*<<< orphan*/  is_master ; 
 scalar_t__* matrix ; 
 scalar_t__* matrix_debouncing ; 
 int /*<<< orphan*/  matrix_init_quantum () ; 
 int /*<<< orphan*/  unselect_rows () ; 

void matrix_init(void) {
  debug_enable = true;
  debug_matrix = true;
  debug_mouse = true;
  // initialize row and col
  unselect_rows();
  init_cols();

  TX_RX_LED_INIT;

  #ifdef DISABLE_PROMICRO_LEDs
    PORTD |= (1<<5);
    PORTB |= (1<<0);
  #endif

  // initialize matrix state: all keys off
  for (uint8_t i=0; i < MATRIX_ROWS; i++) {
      matrix[i] = 0;
      matrix_debouncing[i] = 0;
  }

  is_master = has_usb();

  matrix_init_quantum();
}