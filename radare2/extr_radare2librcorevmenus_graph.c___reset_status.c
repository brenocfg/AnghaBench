#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  anal; int /*<<< orphan*/  offset; } ;
struct TYPE_6__ {int /*<<< orphan*/  mainCol; TYPE_5__* core; int /*<<< orphan*/  addr; int /*<<< orphan*/  fcn; } ;
typedef  TYPE_1__ RCoreVisualViewGraph ;

/* Variables and functions */
 int /*<<< orphan*/  __fcns (TYPE_5__*) ; 
 int /*<<< orphan*/  __seek_cursor (TYPE_1__*) ; 
 int /*<<< orphan*/  __sort (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_anal_get_fcn_at (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __reset_status(RCoreVisualViewGraph *status) {
	status->addr = status->core->offset;
	status->fcn = r_anal_get_fcn_at (status->core->anal, status->addr, 0);
	
	status->mainCol = __fcns (status->core);
	__sort (status, status->mainCol);
	__seek_cursor (status);

	return;
}