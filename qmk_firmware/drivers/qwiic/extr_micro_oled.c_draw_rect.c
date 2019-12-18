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
 int /*<<< orphan*/  draw_line_hori (int,int,int,int,int) ; 
 int /*<<< orphan*/  draw_line_vert (int,int,int,int,int) ; 

void draw_rect(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t color, uint8_t mode) {
    uint8_t tempHeight;

    draw_line_hori(x, y, width, color, mode);
    draw_line_hori(x, y + height - 1, width, color, mode);

    tempHeight = height - 2;

    // skip drawing vertical lines to avoid overlapping of pixel that will
    // affect XOR plot if no pixel in between horizontal lines
    if (tempHeight < 1) return;

    draw_line_vert(x, y + 1, tempHeight, color, mode);
    draw_line_vert(x + width - 1, y + 1, tempHeight, color, mode);
}