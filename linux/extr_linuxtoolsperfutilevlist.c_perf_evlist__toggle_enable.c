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
struct perf_evlist {scalar_t__ enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  perf_evlist__disable (struct perf_evlist*) ; 
 int /*<<< orphan*/  perf_evlist__enable (struct perf_evlist*) ; 
 int /*<<< orphan*/  stub1 (struct perf_evlist*) ; 

void perf_evlist__toggle_enable(struct perf_evlist *evlist)
{
	(evlist->enabled ? perf_evlist__disable : perf_evlist__enable)(evlist);
}