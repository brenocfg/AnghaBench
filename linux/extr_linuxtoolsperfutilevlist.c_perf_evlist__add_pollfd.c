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
struct perf_evlist {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  POLLIN ; 
 int __perf_evlist__add_pollfd (struct perf_evlist*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int perf_evlist__add_pollfd(struct perf_evlist *evlist, int fd)
{
	return __perf_evlist__add_pollfd(evlist, fd, NULL, POLLIN);
}