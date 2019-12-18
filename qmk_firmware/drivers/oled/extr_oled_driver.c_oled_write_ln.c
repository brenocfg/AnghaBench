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
 int /*<<< orphan*/  oled_advance_page (int) ; 
 int /*<<< orphan*/  oled_write (char const*,int) ; 

void oled_write_ln(const char *data, bool invert) {
    oled_write(data, invert);
    oled_advance_page(true);
}