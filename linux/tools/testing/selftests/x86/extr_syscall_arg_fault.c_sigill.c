#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__* gregs; } ;
struct TYPE_4__ {TYPE_1__ uc_mcontext; } ;
typedef  TYPE_2__ ucontext_t ;
typedef  int /*<<< orphan*/  siginfo_t ;

/* Variables and functions */
 size_t REG_IP ; 
 int /*<<< orphan*/  jmpbuf ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  siglongjmp (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void sigill(int sig, siginfo_t *info, void *ctx_void)
{
	ucontext_t *ctx = (ucontext_t*)ctx_void;
	unsigned short *ip = (unsigned short *)ctx->uc_mcontext.gregs[REG_IP];

	if (*ip == 0x0b0f) {
		/* one of the ud2 instructions faulted */
		printf("[OK]\tSYSCALL returned normally\n");
	} else {
		printf("[SKIP]\tIllegal instruction\n");
	}
	siglongjmp(jmpbuf, 1);
}