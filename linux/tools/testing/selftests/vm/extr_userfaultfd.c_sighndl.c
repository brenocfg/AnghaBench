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
typedef  int /*<<< orphan*/  siginfo_t ;

/* Variables and functions */
 int SIGBUS ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/ * sigbuf ; 
 int /*<<< orphan*/  siglongjmp (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void sighndl(int sig, siginfo_t *siginfo, void *ptr)
{
	if (sig == SIGBUS) {
		if (sigbuf)
			siglongjmp(*sigbuf, 1);
		abort();
	}
}