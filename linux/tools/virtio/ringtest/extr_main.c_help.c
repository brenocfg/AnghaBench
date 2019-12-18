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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int) ; 
 int ring_size ; 
 int runcycles ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void help(void)
{
	fprintf(stderr, "Usage: <test> [--help]"
		" [--host-affinity H]"
		" [--guest-affinity G]"
		" [--ring-size R (default: %d)]"
		" [--run-cycles C (default: %d)]"
		" [--batch b]"
		" [--outstanding o]"
		" [--param p]"
		" [--sleep]"
		" [--relax]"
		" [--exit]"
		"\n",
		ring_size,
		runcycles);
}