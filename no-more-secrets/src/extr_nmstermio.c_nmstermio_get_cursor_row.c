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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  STDIN_FILENO ; 
 int /*<<< orphan*/  STDOUT_FILENO ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int read (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int write (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

int nmstermio_get_cursor_row(void) {
	int i, r;
	int row = 0;
	char buf[10];
	char *cmd = "\033[6n";

	memset(buf, 0, sizeof(buf));

	r = write(STDOUT_FILENO, cmd, strlen(cmd));

	r = read(STDIN_FILENO, buf, sizeof(buf));

	for (i = 0; i < r; ++i) {
		if (buf[i] == 27 || buf[i] == '[') {
			continue;
		}

		if (buf[i] >= '0' && buf[i] <= '9') {
			row = (row * 10) + (buf[i] - '0');
		}
		
		if (buf[i] == ';' || buf[i] == 'R' || buf[i] == 0) {
			break;
		}
	}
	
	return row;
}