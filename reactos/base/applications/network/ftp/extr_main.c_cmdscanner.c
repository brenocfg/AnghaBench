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
struct cmd {int /*<<< orphan*/  (* c_handler ) (scalar_t__,int /*<<< orphan*/ *) ;scalar_t__ c_bell; scalar_t__ c_conn; } ;

/* Variables and functions */
 scalar_t__ bell ; 
 int /*<<< orphan*/  connected ; 
 scalar_t__ feof (int /*<<< orphan*/ ) ; 
 scalar_t__ ferror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 scalar_t__ fromatty ; 
 struct cmd* getcmd (int /*<<< orphan*/ ) ; 
 scalar_t__ gets (scalar_t__*) ; 
 int /*<<< orphan*/  help (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__* line ; 
 int /*<<< orphan*/  makeargv () ; 
 scalar_t__ margc ; 
 int /*<<< orphan*/ * margv ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  putchar (char) ; 
 int /*<<< orphan*/  quit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  stub1 (scalar_t__,int /*<<< orphan*/ *) ; 

void cmdscanner(int top)
{
	register struct cmd *c;

	if (!top)
		(void) putchar('\n');
	for (;;) {
		(void) fflush(stdout);
		if (fromatty) {
			printf("ftp> ");
			(void) fflush(stdout);
		}
		if (gets(line) == 0) {
			if (feof(stdin) || ferror(stdin))
				quit(0, NULL);
			break;
		}
		if (line[0] == 0)
			break;
		makeargv();
		if (margc == 0) {
			continue;
		}
		c = getcmd(margv[0]);
		if (c == (struct cmd *)-1) {
			printf("?Ambiguous command\n");
			continue;
		}
		if (c == 0) {
			printf("?Invalid command\n");
			continue;
		}
		if (c->c_conn && !connected) {
			printf ("Not connected.\n");
			continue;
		}
		(*c->c_handler)(margc, margv);
		if (bell && c->c_bell)
			(void) putchar('\007');
		if (c->c_handler != help)
			break;
	}
	(void) fflush(stdout);
//	(void) signal(SIGINT, intr);
//	(void) signal(SIGPIPE, lostpeer);
}