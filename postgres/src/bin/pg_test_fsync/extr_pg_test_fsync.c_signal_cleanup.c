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
 int /*<<< orphan*/  filename ; 
 scalar_t__ needs_unlink ; 
 int /*<<< orphan*/  puts (char*) ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
signal_cleanup(int signum)
{
	/* Delete the file if it exists. Ignore errors */
	if (needs_unlink)
		unlink(filename);
	/* Finish incomplete line on stdout */
	puts("");
	exit(signum);
}