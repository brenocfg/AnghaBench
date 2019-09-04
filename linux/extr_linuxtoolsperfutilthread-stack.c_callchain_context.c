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

/* Variables and functions */
 scalar_t__ PERF_CONTEXT_KERNEL ; 
 scalar_t__ PERF_CONTEXT_USER ; 

__attribute__((used)) static inline u64 callchain_context(u64 ip, u64 kernel_start)
{
	return ip < kernel_start ? PERF_CONTEXT_USER : PERF_CONTEXT_KERNEL;
}