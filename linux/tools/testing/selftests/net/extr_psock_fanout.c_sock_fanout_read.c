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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int sock_fanout_read_ring (int,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int sock_fanout_read(int fds[], char *rings[], const int expect[])
{
	int ret[2];

	ret[0] = sock_fanout_read_ring(fds[0], rings[0]);
	ret[1] = sock_fanout_read_ring(fds[1], rings[1]);

	fprintf(stderr, "info: count=%d,%d, expect=%d,%d\n",
			ret[0], ret[1], expect[0], expect[1]);

	if ((!(ret[0] == expect[0] && ret[1] == expect[1])) &&
	    (!(ret[0] == expect[1] && ret[1] == expect[0]))) {
		fprintf(stderr, "warning: incorrect queue lengths\n");
		return 1;
	}

	return 0;
}