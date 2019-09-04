#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {void* Mode; int /*<<< orphan*/  Offset; } ;
struct TYPE_8__ {void* Mode; int /*<<< orphan*/  Offset; } ;
struct TYPE_7__ {void* Mode; int /*<<< orphan*/  Offset; } ;
struct TYPE_10__ {TYPE_4__ AddrStack; TYPE_3__ AddrPC; TYPE_2__ AddrFrame; } ;
struct TYPE_6__ {int /*<<< orphan*/  Esp; int /*<<< orphan*/  Ebp; int /*<<< orphan*/  Eip; } ;
struct stack_trace {TYPE_5__ frame; int /*<<< orphan*/  image_type; TYPE_1__ context; int /*<<< orphan*/  instruction_ptr; } ;

/* Variables and functions */
 void* AddrModeFlat ; 
 int /*<<< orphan*/  IMAGE_FILE_MACHINE_I386 ; 

__attribute__((used)) static inline void init_instruction_data(struct stack_trace *trace)
{
#ifdef _WIN64
	trace->instruction_ptr = trace->context.Rip;
	trace->frame.AddrPC.Offset = trace->instruction_ptr;
	trace->frame.AddrFrame.Offset = trace->context.Rbp;
	trace->frame.AddrStack.Offset = trace->context.Rsp;
	trace->image_type = IMAGE_FILE_MACHINE_AMD64;
#else
	trace->instruction_ptr = trace->context.Eip;
	trace->frame.AddrPC.Offset = trace->instruction_ptr;
	trace->frame.AddrFrame.Offset = trace->context.Ebp;
	trace->frame.AddrStack.Offset = trace->context.Esp;
	trace->image_type = IMAGE_FILE_MACHINE_I386;
#endif

	trace->frame.AddrFrame.Mode = AddrModeFlat;
	trace->frame.AddrPC.Mode = AddrModeFlat;
	trace->frame.AddrStack.Mode = AddrModeFlat;
}