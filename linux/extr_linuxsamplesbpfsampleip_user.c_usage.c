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
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void usage(void)
{
	printf("USAGE: sampleip [-F freq] [duration]\n");
	printf("       -F freq    # sample frequency (Hertz), default 99\n");
	printf("       duration   # sampling duration (seconds), default 5\n");
}