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
 int perf_evlist__poll (int /*<<< orphan*/ *,int) ; 

int evlist__poll(struct evlist *evlist, int timeout)
{
	return perf_evlist__poll(&evlist->core, timeout);
}