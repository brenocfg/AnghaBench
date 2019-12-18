#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ut64 ;
struct TYPE_6__ {TYPE_1__* core; int /*<<< orphan*/  cur; int /*<<< orphan*/  visited; } ;
struct TYPE_5__ {int /*<<< orphan*/  anal; } ;
typedef  TYPE_2__ RCoreAnalPaths ;
typedef  int /*<<< orphan*/  PJ ;

/* Variables and functions */
 scalar_t__ UT64_MAX ; 
 int /*<<< orphan*/  analPaths (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dict_get (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  r_anal_bb_from_offset (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void analPathFollow(RCoreAnalPaths *p, ut64 addr, PJ *pj) {
	if (addr == UT64_MAX) {
		return;
	}
	if (!dict_get (&p->visited, addr)) {
		p->cur = r_anal_bb_from_offset (p->core->anal, addr);
		analPaths (p, pj);
	}
}