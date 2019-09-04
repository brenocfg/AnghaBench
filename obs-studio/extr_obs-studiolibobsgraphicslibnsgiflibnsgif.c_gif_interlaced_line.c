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

__attribute__((used)) static unsigned int gif_interlaced_line(int height, int y) {
    if ((y << 3) < height) return (y << 3);
    y -= ((height + 7) >> 3);
    if ((y << 3) < (height - 4)) return (y << 3) + 4;
    y -= ((height + 3) >> 3);
    if ((y << 2) < (height - 2)) return (y << 2) + 2;
    y -= ((height + 1) >> 2);
    return (y << 1) + 1;
}