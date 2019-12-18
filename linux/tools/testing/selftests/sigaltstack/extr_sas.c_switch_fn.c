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

/* Variables and functions */
 int /*<<< orphan*/  SIGUSR2 ; 
 int /*<<< orphan*/  ksft_print_msg (char*) ; 
 int /*<<< orphan*/  raise (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sc ; 
 int /*<<< orphan*/  setcontext (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void switch_fn(void)
{
	ksft_print_msg("[RUN]\tswitched to user ctx\n");
	raise(SIGUSR2);
	setcontext(&sc);
}