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
struct TYPE_5__ {int /*<<< orphan*/ * ContextRecord; TYPE_1__* ExceptionRecord; } ;
struct TYPE_4__ {scalar_t__ ExceptionCode; scalar_t__* ExceptionInformation; } ;
typedef  TYPE_1__ EXCEPTION_RECORD ;
typedef  TYPE_2__ EXCEPTION_POINTERS ;
typedef  int /*<<< orphan*/  CONTEXT ;

/* Variables and functions */
 scalar_t__ EXCEPTION_ACCESS_VIOLATION ; 
 int EXCEPTION_CONTINUE_EXECUTION ; 
 int EXCEPTION_CONTINUE_SEARCH ; 
 scalar_t__ SUCCESS ; 
 scalar_t__ phpdbg_watchpoint_segfault_handler (void*) ; 

int phpdbg_exception_handler_win32(EXCEPTION_POINTERS *xp) {
	EXCEPTION_RECORD *xr = xp->ExceptionRecord;
	CONTEXT *xc = xp->ContextRecord;

	if(xr->ExceptionCode == EXCEPTION_ACCESS_VIOLATION) {

		if (phpdbg_watchpoint_segfault_handler((void *)xr->ExceptionInformation[1]) == SUCCESS) {
			return EXCEPTION_CONTINUE_EXECUTION;
		}
	}

	return EXCEPTION_CONTINUE_SEARCH;
}