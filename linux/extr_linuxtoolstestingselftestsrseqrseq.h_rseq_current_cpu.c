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
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 scalar_t__ rseq_current_cpu_raw () ; 
 scalar_t__ rseq_fallback_current_cpu () ; 
 scalar_t__ rseq_unlikely (int) ; 

__attribute__((used)) static inline uint32_t rseq_current_cpu(void)
{
	int32_t cpu;

	cpu = rseq_current_cpu_raw();
	if (rseq_unlikely(cpu < 0))
		cpu = rseq_fallback_current_cpu();
	return cpu;
}