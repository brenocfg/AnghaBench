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
struct TYPE_4__ {int /*<<< orphan*/  ptr; } ;
struct TYPE_5__ {int /*<<< orphan*/  size; TYPE_1__ addr; } ;
typedef  TYPE_2__ phpdbg_watchpoint_t ;

/* Variables and functions */
 int /*<<< orphan*/  mprotect (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  phpdbg_get_page_boundary (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phpdbg_get_total_page_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void phpdbg_change_watchpoint_access(phpdbg_watchpoint_t *watch, int access) {
	/* pagesize is assumed to be in the range of 2^x */
	mprotect(phpdbg_get_page_boundary(watch->addr.ptr), phpdbg_get_total_page_size(watch->addr.ptr, watch->size), access);
}