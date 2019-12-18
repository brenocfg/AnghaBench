#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char* cmd; } ;

/* Variables and functions */
 TYPE_1__* bbcmds ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int run (int,char const*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

int main(int argc, char **argv) {
	int i;
	for (i = 0; bbcmds[i].cmd; i++) {
		if (!strcmp (bbcmds[i].cmd, argv[0])) {
			const char *arg = argc > 1? argv[1]: NULL;
			return run (i, arg);
		}
	}
	if (argc > 1) {
		for (i = 0; bbcmds[i].cmd; i++) {
			if (!strcmp (bbcmds[i].cmd, argv[1])) {
				const char *arg = argc > 2? argv[2]: NULL;
				return run (i, arg);
			}
		}
	}
	for (i = 0; bbcmds[i].cmd; i++) {
		printf ("%s\n", bbcmds[i].cmd);
	}
	return 1;
}