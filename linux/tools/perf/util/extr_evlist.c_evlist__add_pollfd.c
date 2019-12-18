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
struct evlist {int /*<<< orphan*/  core; } ;

/* Variables and functions */
 int /*<<< orphan*/  POLLIN ; 
 int perf_evlist__add_pollfd (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int evlist__add_pollfd(struct evlist *evlist, int fd)
{
	return perf_evlist__add_pollfd(&evlist->core, fd, NULL, POLLIN);
}