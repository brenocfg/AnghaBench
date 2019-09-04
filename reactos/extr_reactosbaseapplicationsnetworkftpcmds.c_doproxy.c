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
struct cmd {int /*<<< orphan*/  (* c_handler ) (int,char const**) ;scalar_t__ c_conn; int /*<<< orphan*/  c_proxy; } ;
typedef  int /*<<< orphan*/  jmp_buf ;

/* Variables and functions */
 int code ; 
 scalar_t__ connected ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gets (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * line ; 
 int /*<<< orphan*/  makeargv () ; 
 int margc ; 
 char** margv ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int proxflag ; 
 int /*<<< orphan*/  pswitch (int) ; 
 scalar_t__ setjmp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strcat (int /*<<< orphan*/ *,char*) ; 
 size_t strlen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int,char const**) ; 

void doproxy(int argc, const char *argv[])
{
	register struct cmd *c;
	struct cmd *getcmd();
//	extern struct cmd cmdtab[];
	extern jmp_buf abortprox;

	if (argc < 2) {
		(void) strcat(line, " ");
		printf("(command) ");
		(void) fflush(stdout);
		(void) gets(&line[strlen(line)]);
		makeargv();
		argc = margc;
		argv = margv;
	}
	if (argc < 2) {
		printf("usage:%s command\n", argv[0]);
		(void) fflush(stdout);
		code = -1;
		return;
	}
	c = getcmd(argv[1]);
	if (c == (struct cmd *) -1) {
		printf("?Ambiguous command\n");
		(void) fflush(stdout);
		code = -1;
		return;
	}
	if (c == 0) {
		printf("?Invalid command\n");
		(void) fflush(stdout);
		code = -1;
		return;
	}
	if (!c->c_proxy) {
		printf("?Invalid proxy command\n");
		(void) fflush(stdout);
		code = -1;
		return;
	}
	if (setjmp(abortprox)) {
		code = -1;
		return;
	}
//	oldintr = signal(SIGINT, proxabort);
	pswitch(1);
	if (c->c_conn && !connected) {
		printf("Not connected\n");
		(void) fflush(stdout);
		pswitch(0);
//		(void) signal(SIGINT, oldintr);
		code = -1;
		return;
	}
	(*c->c_handler)(argc-1, argv+1);
	if (connected) {
		proxflag = 1;
	}
	else {
		proxflag = 0;
	}
	pswitch(0);
//	(void) signal(SIGINT, oldintr);
}