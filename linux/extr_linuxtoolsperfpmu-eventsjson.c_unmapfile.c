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
 int /*<<< orphan*/  _SC_PAGESIZE ; 
 int /*<<< orphan*/  munmap (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  roundup (size_t,unsigned int) ; 
 unsigned int sysconf (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void unmapfile(char *map, size_t size)
{
	unsigned ps = sysconf(_SC_PAGESIZE);
	munmap(map, roundup(size, ps));
}