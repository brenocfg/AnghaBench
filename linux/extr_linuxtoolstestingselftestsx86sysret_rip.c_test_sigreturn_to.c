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
 int /*<<< orphan*/  SIGUSR1 ; 
 int /*<<< orphan*/  printf (char*,unsigned long) ; 
 int /*<<< orphan*/  raise (int /*<<< orphan*/ ) ; 
 unsigned long rip ; 

__attribute__((used)) static void test_sigreturn_to(unsigned long ip)
{
	rip = ip;
	printf("[RUN]\tsigreturn to 0x%lx\n", ip);
	raise(SIGUSR1);
}