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
struct perf_error_ops {int dummy; } ;

/* Variables and functions */
 struct perf_error_ops default_eops ; 
 struct perf_error_ops* perf_eops ; 

int perf_error__register(struct perf_error_ops *eops)
{
	if (perf_eops != &default_eops)
		return -1;

	perf_eops = eops;
	return 0;
}