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
struct evlist {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct evlist* evlist__new () ; 
 int ppc__setup_book3s_hv (struct perf_kvm_stat*,struct evlist*) ; 

__attribute__((used)) static int ppc__setup_kvm_tp(struct perf_kvm_stat *kvm)
{
	struct evlist *evlist = evlist__new();

	if (evlist == NULL)
		return -ENOMEM;

	/* Right now, only supported on book3s_hv */
	return ppc__setup_book3s_hv(kvm, evlist);
}