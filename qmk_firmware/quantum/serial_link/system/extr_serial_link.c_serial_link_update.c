#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
typedef  scalar_t__ systime_t ;
struct TYPE_5__ {scalar_t__* rows; } ;
typedef  TYPE_1__ matrix_object_t ;

/* Variables and functions */
 size_t MATRIX_ROWS ; 
 scalar_t__ US2ST (int) ; 
 TYPE_1__* begin_write_keyboard_matrix () ; 
 int* begin_write_serial_link_connected () ; 
 scalar_t__ chVTGetSystemTimeX () ; 
 int /*<<< orphan*/  end_write_keyboard_matrix () ; 
 int /*<<< orphan*/  end_write_serial_link_connected () ; 
 TYPE_1__ last_matrix ; 
 scalar_t__ last_update ; 
 scalar_t__ matrix_get_row (size_t) ; 
 int /*<<< orphan*/  matrix_set_remote (scalar_t__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* read_keyboard_matrix (int /*<<< orphan*/ ) ; 
 scalar_t__ read_serial_link_connected () ; 
 int serial_link_connected ; 

void serial_link_update(void) {
    if (read_serial_link_connected()) {
        serial_link_connected = true;
    }

    matrix_object_t matrix;
    bool            changed = false;
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        matrix.rows[i] = matrix_get_row(i);
        changed |= matrix.rows[i] != last_matrix.rows[i];
    }

    systime_t current_time = chVTGetSystemTimeX();
    systime_t delta        = current_time - last_update;
    if (changed || delta > US2ST(5000)) {
        last_update        = current_time;
        last_matrix        = matrix;
        matrix_object_t* m = begin_write_keyboard_matrix();
        for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
            m->rows[i] = matrix.rows[i];
        }
        end_write_keyboard_matrix();
        *begin_write_serial_link_connected() = true;
        end_write_serial_link_connected();
    }

    matrix_object_t* m = read_keyboard_matrix(0);
    if (m) {
        matrix_set_remote(m->rows, 0);
    }
}