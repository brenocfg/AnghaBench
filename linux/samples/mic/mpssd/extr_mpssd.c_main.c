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
typedef  int pid_t ;

/* Variables and functions */
 char* LOGFILE_NAME ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fopen (char*,char*) ; 
 int fork () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int init_mic_list () ; 
 int /*<<< orphan*/  logfp ; 
 int /*<<< orphan*/  mpsslog (char*,...) ; 
 char* myname ; 
 int /*<<< orphan*/  start_daemon () ; 
 int /*<<< orphan*/  stderr ; 

int
main(int argc, char *argv[])
{
	int cnt;
	pid_t pid;

	myname = argv[0];

	logfp = fopen(LOGFILE_NAME, "a+");
	if (!logfp) {
		fprintf(stderr, "cannot open logfile '%s'\n", LOGFILE_NAME);
		exit(1);
	}
	pid = fork();
	switch (pid) {
	case 0:
		break;
	case -1:
		exit(2);
	default:
		exit(0);
	}

	mpsslog("MIC Daemon start\n");

	cnt = init_mic_list();
	if (cnt == 0) {
		mpsslog("MIC module not loaded\n");
		exit(3);
	}
	mpsslog("MIC found %d devices\n", cnt);

	start_daemon();

	exit(0);
}