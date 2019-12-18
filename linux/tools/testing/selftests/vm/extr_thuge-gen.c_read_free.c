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
 unsigned long getpagesize () ; 
 unsigned long read_sysfs (int,char*,unsigned long) ; 

unsigned long read_free(unsigned long ps)
{
	return read_sysfs(ps != getpagesize(),
			"/sys/kernel/mm/hugepages/hugepages-%lukB/free_hugepages",
			ps >> 10);
}