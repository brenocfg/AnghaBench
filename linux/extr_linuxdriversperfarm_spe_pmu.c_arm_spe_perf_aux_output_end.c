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
typedef  scalar_t__ u64 ;
struct perf_output_handle {scalar_t__ head; } ;
struct arm_spe_pmu_buf {scalar_t__ snapshot; scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ PERF_IDX2OFF (scalar_t__,struct arm_spe_pmu_buf*) ; 
 int /*<<< orphan*/  SYS_PMBPTR_EL1 ; 
 int /*<<< orphan*/  perf_aux_output_end (struct perf_output_handle*,scalar_t__) ; 
 struct arm_spe_pmu_buf* perf_get_aux (struct perf_output_handle*) ; 
 scalar_t__ read_sysreg_s (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void arm_spe_perf_aux_output_end(struct perf_output_handle *handle)
{
	struct arm_spe_pmu_buf *buf = perf_get_aux(handle);
	u64 offset, size;

	offset = read_sysreg_s(SYS_PMBPTR_EL1) - (u64)buf->base;
	size = offset - PERF_IDX2OFF(handle->head, buf);

	if (buf->snapshot)
		handle->head = offset;

	perf_aux_output_end(handle, size);
}