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
 int MAXPATHLEN ; 
 scalar_t__ chdir (char const*) ; 
 int code ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 char* getcwd (char*,int) ; 
 int /*<<< orphan*/  globulize (char const**) ; 
 char* home ; 
 int /*<<< orphan*/  perror (char const*) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 int /*<<< orphan*/  stdout ; 

void lcd(int argc, const char *argv[])
{
	char buf[MAXPATHLEN];

	if (argc < 2)
		argc++, argv[1] = home;
	if (argc != 2) {
		printf("usage:%s local-directory\n", argv[0]);
		(void) fflush(stdout);
		code = -1;
		return;
	}
	if (!globulize(&argv[1])) {
		code = -1;
		return;
	}
	if (chdir(argv[1]) < 0) {
		perror(argv[1]);
		code = -1;
		return;
	}
	printf("Local directory now %s\n", getcwd(buf,sizeof(buf)));
	(void) fflush(stdout);
	code = 0;
}