#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct unwind_state {int depth; unsigned long ip; } ;
struct _Unwind_Context {int dummy; } ;
typedef  int /*<<< orphan*/  _Unwind_Reason_Code ;

/* Variables and functions */
 unsigned long SYS_getpid ; 
 int /*<<< orphan*/  _URC_NORMAL_STOP ; 
 int /*<<< orphan*/  _URC_NO_REASON ; 
 unsigned long _Unwind_GetGR (struct _Unwind_Context*,int) ; 
 unsigned long _Unwind_GetIP (struct _Unwind_Context*) ; 
 unsigned long getpid () ; 
 int /*<<< orphan*/  nerrs ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 unsigned long return_address ; 

_Unwind_Reason_Code trace_fn(struct _Unwind_Context * ctx, void *opaque)
{
	struct unwind_state *state = opaque;
	unsigned long ip = _Unwind_GetIP(ctx);

	if (state->depth == -1) {
		if (ip == state->ip)
			state->depth = 0;
		else
			return _URC_NO_REASON;	/* Not there yet */
	}
	printf("\t  0x%lx\n", ip);

	if (ip == return_address) {
		/* Here we are. */
		unsigned long eax = _Unwind_GetGR(ctx, 0);
		unsigned long ecx = _Unwind_GetGR(ctx, 1);
		unsigned long edx = _Unwind_GetGR(ctx, 2);
		unsigned long ebx = _Unwind_GetGR(ctx, 3);
		unsigned long ebp = _Unwind_GetGR(ctx, 5);
		unsigned long esi = _Unwind_GetGR(ctx, 6);
		unsigned long edi = _Unwind_GetGR(ctx, 7);
		bool ok = (eax == SYS_getpid || eax == getpid()) &&
			ebx == 1 && ecx == 2 && edx == 3 &&
			esi == 4 && edi == 5 && ebp == 6;

		if (!ok)
			nerrs++;
		printf("[%s]\t  NR = %ld, args = %ld, %ld, %ld, %ld, %ld, %ld\n",
		       (ok ? "OK" : "FAIL"),
		       eax, ebx, ecx, edx, esi, edi, ebp);

		return _URC_NORMAL_STOP;
	} else {
		state->depth++;
		return _URC_NO_REASON;
	}
}