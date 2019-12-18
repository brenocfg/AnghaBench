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
struct termios {int c_lflag; } ;

/* Variables and functions */
 int ECHO ; 
 int ICANON ; 
 int /*<<< orphan*/  STDIN_FILENO ; 
 int /*<<< orphan*/  TCSAFLUSH ; 
 int /*<<< orphan*/  TCSANOW ; 
 int /*<<< orphan*/  freopen (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isatty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdin ; 
 int tcgetattr (int /*<<< orphan*/ ,struct termios*) ; 
 int tcsetattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct termios*) ; 

__attribute__((used)) static void nmstermio_set_terminal(int s) {
	struct termios tp;
	static struct termios save;
	static int state = 1;

	if (!isatty(STDIN_FILENO)) {
		stdin = freopen("/dev/tty", "r", stdin);
	}
	
	if (s == 0) {
		if (tcgetattr(STDIN_FILENO, &tp) == -1) {
			return;
		}

		save = tp;
		
		tp.c_lflag &=(~ICANON & ~ECHO);
		
		if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &tp) == -1) {
			return;
		}
	} else {
		if (state == 0 && tcsetattr(STDIN_FILENO, TCSANOW, &save) == -1)
			return;
	}
	
	state = s;
}