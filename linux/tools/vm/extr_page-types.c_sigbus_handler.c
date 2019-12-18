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
struct TYPE_3__ {int /*<<< orphan*/ * si_addr; } ;
typedef  TYPE_1__ siginfo_t ;

/* Variables and functions */
 int /*<<< orphan*/ * sigbus_addr ; 
 int /*<<< orphan*/  sigbus_jmp ; 
 int /*<<< orphan*/  siglongjmp (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void sigbus_handler(int sig, siginfo_t *info, void *ucontex)
{
	(void)sig;
	(void)ucontex;
	sigbus_addr = info ? info->si_addr : NULL;
	siglongjmp(sigbus_jmp, 1);
}