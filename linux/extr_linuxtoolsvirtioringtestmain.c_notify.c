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
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  vmentry () ; 
 int /*<<< orphan*/  vmexit () ; 
 int write (int,unsigned long long*,int) ; 

void notify(int fd)
{
	unsigned long long v = 1;
	int r;

	vmexit();
	r = write(fd, &v, sizeof v);
	assert(r == sizeof v);
	vmentry();
}