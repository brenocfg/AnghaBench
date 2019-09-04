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
typedef  scalar_t__ u8 ;
typedef  int u64 ;

/* Variables and functions */
 scalar_t__ PERF_COUNT_HW_CACHE_MAX ; 
 scalar_t__ PERF_COUNT_HW_CACHE_OP_MAX ; 
 scalar_t__ PERF_COUNT_HW_CACHE_RESULT_MAX ; 
 int __perf_evsel__hw_cache_type_op_res_name (scalar_t__,scalar_t__,scalar_t__,char*,size_t) ; 
 int /*<<< orphan*/  perf_evsel__is_cache_op_valid (scalar_t__,scalar_t__) ; 
 int scnprintf (char*,size_t,char*,char const*) ; 

__attribute__((used)) static int __perf_evsel__hw_cache_name(u64 config, char *bf, size_t size)
{
	u8 op, result, type = (config >>  0) & 0xff;
	const char *err = "unknown-ext-hardware-cache-type";

	if (type >= PERF_COUNT_HW_CACHE_MAX)
		goto out_err;

	op = (config >>  8) & 0xff;
	err = "unknown-ext-hardware-cache-op";
	if (op >= PERF_COUNT_HW_CACHE_OP_MAX)
		goto out_err;

	result = (config >> 16) & 0xff;
	err = "unknown-ext-hardware-cache-result";
	if (result >= PERF_COUNT_HW_CACHE_RESULT_MAX)
		goto out_err;

	err = "invalid-cache";
	if (!perf_evsel__is_cache_op_valid(type, op))
		goto out_err;

	return __perf_evsel__hw_cache_type_op_res_name(type, op, result, bf, size);
out_err:
	return scnprintf(bf, size, "%s", err);
}