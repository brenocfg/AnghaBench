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
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void __attribute__((noreturn)) usage(const char *filepath)
{
	fprintf(stderr, "Usage: %s [-e gre|gue|bare|none] [-i 4|6] [-l len] "
			"[-O 4|6] [-o 4|6] [-n num] [-t secs] [-R] [-T] "
			"[-s <osrc> [-d <odst>] [-S <isrc>] [-D <idst>] "
			"[-x <otos>] [-X <itos>] [-f <isport>] [-F]\n",
		filepath);
	exit(1);
}