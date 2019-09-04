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
struct perf_evlist {int /*<<< orphan*/  pollfd; } ;

/* Variables and functions */
 int fdarray__poll (int /*<<< orphan*/ *,int) ; 

int perf_evlist__poll(struct perf_evlist *evlist, int timeout)
{
	return fdarray__poll(&evlist->pollfd, timeout);
}