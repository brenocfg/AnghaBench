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
 int /*<<< orphan*/  fflush (scalar_t__) ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*) ; 
 scalar_t__ logfile ; 
 scalar_t__ stdout ; 

__attribute__((used)) static void
status_end(void)
{
	fprintf(stdout, "\n");
	fflush(stdout);
	if (logfile)
		fprintf(logfile, "\n");
}