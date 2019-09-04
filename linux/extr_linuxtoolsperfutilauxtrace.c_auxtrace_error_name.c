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
 int PERF_AUXTRACE_ERROR_MAX ; 
 char** auxtrace_error_type_name ; 

__attribute__((used)) static const char *auxtrace_error_name(int type)
{
	const char *error_type_name = NULL;

	if (type < PERF_AUXTRACE_ERROR_MAX)
		error_type_name = auxtrace_error_type_name[type];
	if (!error_type_name)
		error_type_name = "unknown AUX";
	return error_type_name;
}