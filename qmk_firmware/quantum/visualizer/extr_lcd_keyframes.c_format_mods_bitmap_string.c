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
typedef  int uint32_t ;

/* Variables and functions */

__attribute__((used)) static void format_mods_bitmap_string(uint8_t mods, char* buffer) {
    *buffer = ' ';
    ++buffer;

    for (int i = 0; i < 8; i++) {
        uint32_t mask = (1u << i);
        if (mods & mask) {
            *buffer = '1';
        } else {
            *buffer = '0';
        }
        ++buffer;

        if (i == 3) {
            *buffer = ' ';
            ++buffer;
        }
    }
    *buffer = 0;
}