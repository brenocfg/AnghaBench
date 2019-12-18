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
 int /*<<< orphan*/  INVERTDISPLAY ; 
 int /*<<< orphan*/  NORMALDISPLAY ; 
 int /*<<< orphan*/  send_command (int /*<<< orphan*/ ) ; 

void invert_screen(bool invert) {
    if (invert) {
        send_command(INVERTDISPLAY);
    } else {
        send_command(NORMALDISPLAY);
    }
}