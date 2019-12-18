#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {unsigned long ExceptionCode; } ;
struct TYPE_7__ {TYPE_1__ ExceptionRecord; } ;
struct TYPE_8__ {TYPE_2__ Exception; } ;
struct TYPE_9__ {scalar_t__ dwThreadId; scalar_t__ dwProcessId; TYPE_3__ u; } ;
typedef  TYPE_4__ DEBUG_EVENT ;

/* Variables and functions */
#define  EXCEPTION_ACCESS_VIOLATION 132 
#define  EXCEPTION_ARRAY_BOUNDS_EXCEEDED 131 
#define  EXCEPTION_ILLEGAL_INSTRUCTION 130 
#define  EXCEPTION_INT_DIVIDE_BY_ZERO 129 
#define  EXCEPTION_STACK_OVERFLOW 128 
 int __get_w32_excep_name (unsigned long) ; 
 int /*<<< orphan*/  eprintf (char*,int,int,int) ; 

__attribute__((used)) static int __debug_exception_event(DEBUG_EVENT *de) {
	unsigned long code = de->u.Exception.ExceptionRecord.ExceptionCode;
	switch (code) {
	/* fatal exceptions */
	case EXCEPTION_ACCESS_VIOLATION:
	case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:
	case EXCEPTION_ILLEGAL_INSTRUCTION:
	case EXCEPTION_INT_DIVIDE_BY_ZERO:
	case EXCEPTION_STACK_OVERFLOW:
		eprintf ("(%d) Fatal exception (%s) in thread %d\n",
			(int)de->dwProcessId, 
			__get_w32_excep_name (code),
			(int)de->dwThreadId);
		break;
	/* MS_VC_EXCEPTION */
	case 0x406D1388:
		eprintf ("(%d) MS_VC_EXCEPTION (%x) in thread %d\n",
			(int)de->dwProcessId, (int)code, (int)de->dwThreadId);
		return 1;
	default:
		eprintf ("(%d) Unknown exception %x in thread %d\n",
			(int)de->dwProcessId, (int)code, (int)de->dwThreadId);
		break;
	}
	return 0;
}