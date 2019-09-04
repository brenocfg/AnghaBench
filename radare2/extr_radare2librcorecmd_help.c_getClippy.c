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
 int R_AVATAR_ORANGG ; 
 int r_num_rand (int) ; 

__attribute__((used)) static const char *getClippy(int type) {
	if (type == R_AVATAR_ORANGG) {
			return
			"      _______\n"
			"     /       \\      .-%s-.\n"
			"   _| ( o) (o)\\_    | %s |\n"
			"  / _     .\\. | \\  <| %s |\n"
			"  \\| \\   ____ / 7`  | %s |\n"
			"  '|\\|  `---'/      `-%s-'\n"
			"     | /----. \\\n"
			"     | \\___/  |___\n"
			"     `-----'`-----'\n"
			;
	}
	const int choose = r_num_rand (3);
	switch (choose) {
	case 0: return
" .--.     .-%s-.\n"
" | _|     | %s |\n"
" | O O   <  %s |\n"
" |  |  |  | %s |\n"
" || | /   `-%s-'\n"
" |`-'|\n"
" `---'\n";
	case 1: return
" .--.     .-%s-.\n"
" |   \\    | %s |\n"
" | O o   <  %s |\n"
" |   | /  | %s |\n"
" |  ( /   `-%s-'\n"
" |   / \n"
" `--'\n";
	case 2: return
" .--.     .-%s-.\n"
" | _|_    | %s |\n"
" | O O   <  %s |\n"
" |  ||    | %s |\n"
" | _:|    `-%s-'\n"
" |   |\n"
" `---'\n";
	}
	return "";
}