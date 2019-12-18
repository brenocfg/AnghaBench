#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {void* refsCol; void* xrefsCol; scalar_t__ addr; int /*<<< orphan*/  core; TYPE_1__* fcn; int /*<<< orphan*/  mainCol; int /*<<< orphan*/  cur; } ;
struct TYPE_9__ {TYPE_1__* fcn; scalar_t__ addr; } ;
struct TYPE_8__ {scalar_t__ addr; } ;
typedef  TYPE_2__ RCoreVisualViewGraphItem ;
typedef  TYPE_3__ RCoreVisualViewGraph ;

/* Variables and functions */
 void* __refs (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  __reset_status (TYPE_3__*) ; 
 int /*<<< orphan*/  __sort (TYPE_3__*,void*) ; 
 void* __xrefs (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  free ; 
 int /*<<< orphan*/  r_list_free (int /*<<< orphan*/ ) ; 
 TYPE_2__* r_list_get_n (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* r_list_newf (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __sync_status_with_cursor(RCoreVisualViewGraph *status) {
	RCoreVisualViewGraphItem *item = r_list_get_n (status->mainCol, status->cur);
	if (!item) {
		r_list_free (status->mainCol);
		__reset_status (status);
		return;
	}

	status->addr = item->addr;
	status->fcn = item->fcn;

	// Update xrefs and refs columns based on selected element in fcns column
	if (status->fcn && status->fcn->addr) {
		status->xrefsCol = __xrefs (status->core, status->fcn->addr);
		status->refsCol = __refs (status->core, status->fcn->addr);
	} else {
		status->xrefsCol = __xrefs (status->core, status->addr);
		status->refsCol = r_list_newf (free);
	}
	__sort (status, status->xrefsCol);
	__sort (status, status->refsCol);
}