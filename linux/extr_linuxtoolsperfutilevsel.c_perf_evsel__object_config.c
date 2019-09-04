#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {size_t size; int (* init ) (struct perf_evsel*) ;void (* fini ) (struct perf_evsel*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 TYPE_1__ perf_evsel__object ; 

int perf_evsel__object_config(size_t object_size,
			      int (*init)(struct perf_evsel *evsel),
			      void (*fini)(struct perf_evsel *evsel))
{

	if (object_size == 0)
		goto set_methods;

	if (perf_evsel__object.size > object_size)
		return -EINVAL;

	perf_evsel__object.size = object_size;

set_methods:
	if (init != NULL)
		perf_evsel__object.init = init;

	if (fini != NULL)
		perf_evsel__object.fini = fini;

	return 0;
}