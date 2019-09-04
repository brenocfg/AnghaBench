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
struct perf_kvm_stat {int dummy; } ;

/* Variables and functions */
 int ppc__setup_kvm_tp (struct perf_kvm_stat*) ; 

int setup_kvm_events_tp(struct perf_kvm_stat *kvm)
{
	return ppc__setup_kvm_tp(kvm);
}