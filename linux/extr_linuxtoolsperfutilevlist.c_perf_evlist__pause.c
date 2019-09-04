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
 int perf_evlist__set_paused (struct perf_evlist*,int) ; 

__attribute__((used)) static int perf_evlist__pause(struct perf_evlist *evlist)
{
	return perf_evlist__set_paused(evlist, true);
}