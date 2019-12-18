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
struct perf_counts_values {int dummy; } ;
struct perf_counts {int /*<<< orphan*/  values; } ;

/* Variables and functions */
 struct perf_counts_values* xyarray__entry (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static inline struct perf_counts_values*
perf_counts(struct perf_counts *counts, int cpu, int thread)
{
	return xyarray__entry(counts->values, cpu, thread);
}