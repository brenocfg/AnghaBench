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
struct TYPE_2__ {scalar_t__ offset; } ;
struct syscall_tp {TYPE_1__ id; int /*<<< orphan*/  args; } ;
struct evsel {struct syscall_tp* priv; } ;

/* Variables and functions */
 int __tp_field__init_ptr (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static int perf_evsel__init_augmented_syscall_tp_args(struct evsel *evsel)
{
	struct syscall_tp *sc = evsel->priv;

	return __tp_field__init_ptr(&sc->args, sc->id.offset + sizeof(u64));
}