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
 int /*<<< orphan*/  errcontext (char*,char const*) ; 

__attribute__((used)) static void
start_proc_error_callback(void *arg)
{
	const char *gucname = (const char *) arg;

	/* translator: %s is "pltcl.start_proc" or "pltclu.start_proc" */
	errcontext("processing %s parameter", gucname);
}