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
typedef  int uint32_t ;
typedef  int uint16_t ;

/* Variables and functions */

__attribute__((used)) static void format_layer_bitmap_string(uint16_t default_layer, uint16_t layer, char* buffer) {
    for (int i = 0; i < 16; i++) {
        uint32_t mask = (1u << i);
        if (default_layer & mask) {
            if (layer & mask) {
                *buffer = 'B';
            } else {
                *buffer = 'D';
            }
        } else if (layer & mask) {
            *buffer = '1';
        } else {
            *buffer = '0';
        }
        ++buffer;

        if (i == 3 || i == 7 || i == 11) {
            *buffer = ' ';
            ++buffer;
        }
    }
    *buffer = 0;
}