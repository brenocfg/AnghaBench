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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  u8 ;
struct intel_pt {scalar_t__ kernel_start; } ;

/* Variables and functions */
 int /*<<< orphan*/  PERF_RECORD_MISC_KERNEL ; 
 int /*<<< orphan*/  PERF_RECORD_MISC_USER ; 

__attribute__((used)) static inline u8 intel_pt_cpumode(struct intel_pt *pt, uint64_t ip)
{
	return ip >= pt->kernel_start ?
	       PERF_RECORD_MISC_KERNEL :
	       PERF_RECORD_MISC_USER;
}