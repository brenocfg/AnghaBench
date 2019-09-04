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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 size_t fread (char*,int,int,int /*<<< orphan*/ *) ; 
 int pclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/ * popen (char*,char*) ; 
 char* xstrdup (char*) ; 

__attribute__((used)) static char *do_shell(int argc, char *argv[])
{
	FILE *p;
	char buf[256];
	char *cmd;
	size_t nread;
	int i;

	cmd = argv[0];

	p = popen(cmd, "r");
	if (!p) {
		perror(cmd);
		exit(1);
	}

	nread = fread(buf, 1, sizeof(buf), p);
	if (nread == sizeof(buf))
		nread--;

	/* remove trailing new lines */
	while (nread > 0 && buf[nread - 1] == '\n')
		nread--;

	buf[nread] = 0;

	/* replace a new line with a space */
	for (i = 0; i < nread; i++) {
		if (buf[i] == '\n')
			buf[i] = ' ';
	}

	if (pclose(p) == -1) {
		perror(cmd);
		exit(1);
	}

	return xstrdup(buf);
}