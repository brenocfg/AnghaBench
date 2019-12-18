#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct winsize {int /*<<< orphan*/  ws_col; } ;
struct TYPE_5__ {char const** argv; int in; int /*<<< orphan*/  preexec_cb; } ;
struct TYPE_4__ {char* pager_env; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIOCGWINSZ ; 
 int /*<<< orphan*/  X_OK ; 
 scalar_t__ access (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atexit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  dup2 (int,int) ; 
 char* forced_pager ; 
 char* getenv (char*) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct winsize*) ; 
 scalar_t__ isatty (int) ; 
 char const** pager_argv ; 
 int /*<<< orphan*/  pager_columns ; 
 int /*<<< orphan*/  pager_preexec ; 
 TYPE_2__ pager_process ; 
 int /*<<< orphan*/  sigchain_push_common (int /*<<< orphan*/ ) ; 
 int spawned_pager ; 
 scalar_t__ start_command (TYPE_2__*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 TYPE_1__ subcmd_config ; 
 int /*<<< orphan*/  wait_for_pager ; 
 int /*<<< orphan*/  wait_for_pager_signal ; 

void setup_pager(void)
{
	const char *pager = getenv(subcmd_config.pager_env);
	struct winsize sz;

	if (forced_pager)
		pager = forced_pager;
	if (!isatty(1) && !forced_pager)
		return;
	if (ioctl(1, TIOCGWINSZ, &sz) == 0)
		pager_columns = sz.ws_col;
	if (!pager)
		pager = getenv("PAGER");
	if (!(pager || access("/usr/bin/pager", X_OK)))
		pager = "/usr/bin/pager";
	if (!(pager || access("/usr/bin/less", X_OK)))
		pager = "/usr/bin/less";
	if (!pager)
		pager = "cat";
	if (!*pager || !strcmp(pager, "cat"))
		return;

	spawned_pager = 1; /* means we are emitting to terminal */

	/* spawn the pager */
	pager_argv[2] = pager;
	pager_process.argv = pager_argv;
	pager_process.in = -1;
	pager_process.preexec_cb = pager_preexec;

	if (start_command(&pager_process))
		return;

	/* original process continues, but writes to the pipe */
	dup2(pager_process.in, 1);
	if (isatty(2))
		dup2(pager_process.in, 2);
	close(pager_process.in);

	/* this makes sure that the parent terminates after the pager */
	sigchain_push_common(wait_for_pager_signal);
	atexit(wait_for_pager);
}