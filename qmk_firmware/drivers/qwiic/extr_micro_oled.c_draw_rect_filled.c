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
 int /*<<< orphan*/  draw_line_vert (int,int,int,int,int) ; 

void draw_rect_filled(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t color, uint8_t mode) {
    // TODO - need to optimise the memory map draw so that this function will not call pixel one by one
    for (int i = x; i < x + width; i++) {
        draw_line_vert(i, y, height, color, mode);
    }
}