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
struct termios {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCSANOW ; 
 int /*<<< orphan*/  enable_kx (int) ; 
 scalar_t__ getch2_active ; 
 int /*<<< orphan*/  tcsetattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct termios const*) ; 
 int /*<<< orphan*/  tio_orig ; 
 scalar_t__ tio_orig_set ; 
 int /*<<< orphan*/  tty_in ; 

__attribute__((used)) static void do_deactivate_getch2(void)
{
    if (!getch2_active)
        return;

    enable_kx(false);

    if (tio_orig_set) {
        // once set, it will never be set again
        // so we can cast away volatile here
        tcsetattr(tty_in, TCSANOW, (const struct termios *) &tio_orig);
    }

    getch2_active = 0;
}