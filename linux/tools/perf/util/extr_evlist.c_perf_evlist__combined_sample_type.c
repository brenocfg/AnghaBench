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
typedef  int /*<<< orphan*/  u64 ;
struct evlist {scalar_t__ combined_sample_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  __perf_evlist__combined_sample_type (struct evlist*) ; 

u64 perf_evlist__combined_sample_type(struct evlist *evlist)
{
	evlist->combined_sample_type = 0;
	return __perf_evlist__combined_sample_type(evlist);
}