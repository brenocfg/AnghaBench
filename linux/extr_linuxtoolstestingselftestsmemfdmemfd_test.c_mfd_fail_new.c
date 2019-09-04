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
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  printf (char*,char const*,unsigned int) ; 
 int sys_memfd_create (char const*,unsigned int) ; 

__attribute__((used)) static void mfd_fail_new(const char *name, unsigned int flags)
{
	int r;

	r = sys_memfd_create(name, flags);
	if (r >= 0) {
		printf("memfd_create(\"%s\", %u) succeeded, but failure expected\n",
		       name, flags);
		close(r);
		abort();
	}
}