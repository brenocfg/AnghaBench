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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  u8 ;
struct intel_bts {int /*<<< orphan*/  machine; } ;

/* Variables and functions */
 int /*<<< orphan*/  PERF_RECORD_MISC_KERNEL ; 
 int /*<<< orphan*/  PERF_RECORD_MISC_USER ; 
 scalar_t__ machine__kernel_ip (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u8 intel_bts_cpumode(struct intel_bts *bts, uint64_t ip)
{
	return machine__kernel_ip(bts->machine, ip) ?
	       PERF_RECORD_MISC_KERNEL :
	       PERF_RECORD_MISC_USER;
}