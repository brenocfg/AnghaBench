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
#define  SIGINT 129 
#define  SIGUSR1 128 
 int debug ; 
 int exit_requested ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void signal_handler (int signal)
{
	switch (signal) {
	case SIGINT:
		exit_requested = 1;
		if (debug)
			fprintf(stderr, " SIGINT\n");
		break;
	case SIGUSR1:
		if (debug > 1)
			fprintf(stderr, "SIGUSR1\n");
		break;
	}
}