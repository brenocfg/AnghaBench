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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_2__ {int size; } ;
struct perf_record_auxtrace_info {TYPE_1__ header; } ;

/* Variables and functions */

__attribute__((used)) static bool intel_pt_has(struct perf_record_auxtrace_info *auxtrace_info, int pos)
{
	return auxtrace_info->header.size >=
		sizeof(struct perf_record_auxtrace_info) + (sizeof(u64) * (pos + 1));
}