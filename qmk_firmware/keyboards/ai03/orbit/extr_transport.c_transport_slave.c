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
typedef  int /*<<< orphan*/  matrix_row_t ;
struct TYPE_4__ {scalar_t__ current_layer; scalar_t__ nlock_led; scalar_t__ clock_led; scalar_t__ slock_led; int /*<<< orphan*/  backlight_level; } ;
struct TYPE_3__ {int /*<<< orphan*/ * smatrix; } ;

/* Variables and functions */
 int ROWS_PER_HAND ; 
 int /*<<< orphan*/  backlight_set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  led_toggle (int,scalar_t__) ; 
 TYPE_2__ serial_m2s_buffer ; 
 TYPE_1__ serial_s2m_buffer ; 
 int /*<<< orphan*/  set_layer_indicators (scalar_t__) ; 
 scalar_t__ slave_clock_cache ; 
 scalar_t__ slave_layer_cache ; 
 scalar_t__ slave_nlock_cache ; 
 scalar_t__ slave_slock_cache ; 

void transport_slave(matrix_row_t matrix[]) {

  // TODO: if MATRIX_COLS > 8 change to pack()
  for (int i = 0; i < ROWS_PER_HAND; ++i)
  {
    serial_s2m_buffer.smatrix[i] = matrix[i];
  }
  #ifdef BACKLIGHT_ENABLE
    backlight_set(serial_m2s_buffer.backlight_level);
  #endif
  #if defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_SPLIT)
  // Add serial implementation for RGB here
  #endif
  
  if (slave_layer_cache != serial_m2s_buffer.current_layer) {  
	slave_layer_cache = serial_m2s_buffer.current_layer;
	set_layer_indicators(slave_layer_cache);
  }
  
  if (slave_nlock_cache != serial_m2s_buffer.nlock_led) {
	slave_nlock_cache = serial_m2s_buffer.nlock_led;
	led_toggle(3, slave_nlock_cache);
  }
  if (slave_clock_cache != serial_m2s_buffer.clock_led) {
	slave_clock_cache = serial_m2s_buffer.clock_led;
	led_toggle(4, slave_clock_cache);
  }
  if (slave_slock_cache != serial_m2s_buffer.slock_led) {
	slave_slock_cache = serial_m2s_buffer.slock_led;
	led_toggle(5, slave_slock_cache);
  }
  
}