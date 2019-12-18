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
typedef  scalar_t__ u64 ;
struct thread_stack {int /*<<< orphan*/  kernel_start; TYPE_1__* crp; } ;
struct symbol {int dummy; } ;
struct perf_sample {int /*<<< orphan*/  time; scalar_t__ addr; scalar_t__ ip; } ;
struct call_path_root {int /*<<< orphan*/  call_path; } ;
struct call_path {int dummy; } ;
struct addr_location {struct symbol* sym; } ;
struct TYPE_2__ {struct call_path_root* cpr; } ;

/* Variables and functions */
 struct call_path* call_path__findnew (struct call_path_root*,int /*<<< orphan*/ *,struct symbol*,scalar_t__,int /*<<< orphan*/ ) ; 
 int thread_stack__push_cp (struct thread_stack*,scalar_t__,int /*<<< orphan*/ ,scalar_t__,struct call_path*,int,int) ; 

__attribute__((used)) static int thread_stack__bottom(struct thread_stack *ts,
				struct perf_sample *sample,
				struct addr_location *from_al,
				struct addr_location *to_al, u64 ref)
{
	struct call_path_root *cpr = ts->crp->cpr;
	struct call_path *cp;
	struct symbol *sym;
	u64 ip;

	if (sample->ip) {
		ip = sample->ip;
		sym = from_al->sym;
	} else if (sample->addr) {
		ip = sample->addr;
		sym = to_al->sym;
	} else {
		return 0;
	}

	cp = call_path__findnew(cpr, &cpr->call_path, sym, ip,
				ts->kernel_start);

	return thread_stack__push_cp(ts, ip, sample->time, ref, cp,
				     true, false);
}