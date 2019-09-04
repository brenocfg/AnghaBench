#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int uc_flags; } ;
typedef  TYPE_1__ ucontext_t ;
typedef  int /*<<< orphan*/  siginfo_t ;

/* Variables and functions */
 int UC_STRICT_RESTORE_SS ; 
 int /*<<< orphan*/  nerrs ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__* ssptr (TYPE_1__*) ; 

__attribute__((used)) static void sigusr2(int sig, siginfo_t *info, void *ctx_void)
{
	ucontext_t *ctx = (ucontext_t*)ctx_void;

	if (!(ctx->uc_flags & UC_STRICT_RESTORE_SS)) {
		printf("[FAIL]\traise(2) didn't set UC_STRICT_RESTORE_SS\n");
		nerrs++;
		return;  /* We can't do the rest. */
	}

	ctx->uc_flags &= ~UC_STRICT_RESTORE_SS;
	*ssptr(ctx) = 0;

	/* Return.  The kernel should recover without sending another signal. */
}