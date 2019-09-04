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
struct termios {int c_lflag; int* c_cc; } ;

/* Variables and functions */
 int ECHO ; 
 int ICANON ; 
 int /*<<< orphan*/  TCSANOW ; 
 size_t VMIN ; 
 size_t VTIME ; 
 int /*<<< orphan*/  enable_kx (int) ; 
 int getch2_active ; 
 int /*<<< orphan*/  read_terminal ; 
 int /*<<< orphan*/  tcgetattr (int /*<<< orphan*/ ,struct termios*) ; 
 int /*<<< orphan*/  tcsetattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct termios*) ; 
 struct termios tio_orig ; 
 int tio_orig_set ; 
 int /*<<< orphan*/  tty_in ; 

__attribute__((used)) static void do_activate_getch2(void)
{
    if (getch2_active || !read_terminal)
        return;

    enable_kx(true);

    struct termios tio_new;
    tcgetattr(tty_in,&tio_new);

    if (!tio_orig_set) {
        tio_orig = tio_new;
        tio_orig_set = 1;
    }

    tio_new.c_lflag &= ~(ICANON|ECHO); /* Clear ICANON and ECHO. */
    tio_new.c_cc[VMIN] = 1;
    tio_new.c_cc[VTIME] = 0;
    tcsetattr(tty_in,TCSANOW,&tio_new);

    getch2_active = 1;
}