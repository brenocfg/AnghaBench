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
typedef  unsigned long uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  page_idle_fd ; 
 int /*<<< orphan*/  perror (char*) ; 
 int pwrite (int /*<<< orphan*/ ,unsigned long*,int,int) ; 

__attribute__((used)) static int mark_page_idle(unsigned long offset)
{
	static unsigned long off;
	static uint64_t buf;
	int len;

	if ((offset / 64 == off / 64) || buf == 0) {
		buf |= 1UL << (offset % 64);
		off = offset;
		return 0;
	}

	len = pwrite(page_idle_fd, &buf, 8, 8 * (off / 64));
	if (len < 0) {
		perror("mark page idle");
		return len;
	}

	buf = 1UL << (offset % 64);
	off = offset;

	return 0;
}