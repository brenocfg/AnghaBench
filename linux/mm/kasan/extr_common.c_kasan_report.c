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
 int /*<<< orphan*/  __kasan_report (unsigned long,size_t,int,unsigned long) ; 
 int /*<<< orphan*/  user_access_restore (unsigned long) ; 
 unsigned long user_access_save () ; 

void kasan_report(unsigned long addr, size_t size, bool is_write, unsigned long ip)
{
	unsigned long flags = user_access_save();
	__kasan_report(addr, size, is_write, ip);
	user_access_restore(flags);
}