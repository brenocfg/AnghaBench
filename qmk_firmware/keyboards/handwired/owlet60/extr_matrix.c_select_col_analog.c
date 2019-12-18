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
typedef  int uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  mux_pin_control (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * num_in_binary ; 

__attribute__((used)) static void select_col_analog(uint8_t col) {
    switch(col) {

        case 0:
            mux_pin_control(num_in_binary[0]);
            break;
        case 1:
            mux_pin_control(num_in_binary[1]);
            break;
        case 2:
            mux_pin_control(num_in_binary[2]);
            break;
        case 3:
            mux_pin_control(num_in_binary[3]);
            break;
        case 4:
            mux_pin_control(num_in_binary[4]);
            break;
        case 5:
            mux_pin_control(num_in_binary[5]);
            break;
        case 6:
            mux_pin_control(num_in_binary[6]);
            break;
        case 7:
            mux_pin_control(num_in_binary[7]);
            break;
        default:
            break;
    }
}