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
struct TYPE_6__ {scalar_t__ cur_sort; int /*<<< orphan*/  xrefsCol; int /*<<< orphan*/  refsCol; int /*<<< orphan*/  mainCol; } ;
typedef  TYPE_1__ RCoreVisualViewGraph ;

/* Variables and functions */
 scalar_t__ SORT_ADDRESS ; 
 scalar_t__ SORT_NAME ; 
 int /*<<< orphan*/  __seek_cursor (TYPE_1__*) ; 
 int /*<<< orphan*/  __sort (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_return_if_fail (TYPE_1__*) ; 

__attribute__((used)) static void __toggleSort (RCoreVisualViewGraph *status) {
	r_return_if_fail (status);
	status->cur_sort = (status->cur_sort == SORT_ADDRESS)? SORT_NAME: SORT_ADDRESS;
	__sort (status, status->mainCol);
	__sort (status, status->refsCol);
	__sort (status, status->xrefsCol);
	__seek_cursor (status);
}