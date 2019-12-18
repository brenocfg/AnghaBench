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
 int XDPING_DEFAULT_COUNT ; 
 int XDPING_MAX_COUNT ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,int,int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void show_usage(const char *prog)
{
	fprintf(stderr,
		"usage: %s [OPTS] -I interface destination\n\n"
		"OPTS:\n"
		"    -c count		Stop after sending count requests\n"
		"			(default %d, max %d)\n"
		"    -I interface	interface name\n"
		"    -N			Run in driver mode\n"
		"    -s			Server mode\n"
		"    -S			Run in skb mode\n",
		prog, XDPING_DEFAULT_COUNT, XDPING_MAX_COUNT);
}