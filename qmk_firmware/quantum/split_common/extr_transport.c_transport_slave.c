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
typedef  int /*<<< orphan*/  matrix_row_t ;
struct TYPE_4__ {int /*<<< orphan*/  backlight_level; } ;
struct TYPE_3__ {scalar_t__ encoder_state; int /*<<< orphan*/ * smatrix; } ;

/* Variables and functions */
 int ROWS_PER_HAND ; 
 int /*<<< orphan*/  backlight_set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  encoder_state_raw (int /*<<< orphan*/ *) ; 
 TYPE_2__ serial_m2s_buffer ; 
 TYPE_1__ serial_s2m_buffer ; 
 int /*<<< orphan*/  transport_rgblight_slave () ; 

void transport_slave(matrix_row_t matrix[]) {
    transport_rgblight_slave();
    // TODO: if MATRIX_COLS > 8 change to pack()
    for (int i = 0; i < ROWS_PER_HAND; ++i) {
        serial_s2m_buffer.smatrix[i] = matrix[i];
    }
#    ifdef BACKLIGHT_ENABLE
    backlight_set(serial_m2s_buffer.backlight_level);
#    endif

#    ifdef ENCODER_ENABLE
    encoder_state_raw((uint8_t *)serial_s2m_buffer.encoder_state);
#    endif
}