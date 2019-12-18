#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ free; } ;
typedef  scalar_t__ RListFree ;
typedef  TYPE_1__ RList ;
typedef  int /*<<< orphan*/  RDebug ;

/* Variables and functions */
 int /*<<< orphan*/  __r_debug_pid_free ; 
 int /*<<< orphan*/  __r_debug_pid_new (char*,int,char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  desc ; 
 int /*<<< orphan*/  pidlist_cb ; 
 int /*<<< orphan*/  qnxr_pidlist (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_list_append (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* r_list_new () ; 

__attribute__((used)) static RList *r_debug_qnx_pids (RDebug *dbg, int pid) {
	RList *list = r_list_new ();
	if (!list) {
		return NULL;
	}
	list->free = (RListFree)&__r_debug_pid_free;

	/* TODO */
	if (pid) {
		r_list_append (list, __r_debug_pid_new ("(current)", pid, 's', 0));
	} else {
		qnxr_pidlist (desc, list, &pidlist_cb);
	}

	return list;
}