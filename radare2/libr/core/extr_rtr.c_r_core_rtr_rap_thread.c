#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* user; } ;
struct TYPE_4__ {int /*<<< orphan*/  input; int /*<<< orphan*/  core; } ;
typedef  TYPE_1__ RapThread ;
typedef  int RThreadFunctionRet ;
typedef  TYPE_2__ RThread ;

/* Variables and functions */
 int R_TH_REPEAT ; 
 int R_TH_STOP ; 
 scalar_t__ r_core_rtr_rap_run (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static RThreadFunctionRet r_core_rtr_rap_thread (RThread *th) {
	if (!th) {
		return false;
	}
	RapThread *rt = th->user;
	if (!rt || !rt->core) {
		return false;
	}
	return r_core_rtr_rap_run (rt->core, rt->input) ? R_TH_REPEAT : R_TH_STOP;
}