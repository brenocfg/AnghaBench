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
typedef  int uint64_t ;

/* Variables and functions */
 int KPF_HACKERS_BITS ; 
 int KPF_OVERLOADED_BITS ; 

__attribute__((used)) static const char *page_flag_type(uint64_t flag)
{
	if (flag & KPF_HACKERS_BITS)
		return "(r)";
	if (flag & KPF_OVERLOADED_BITS)
		return "(o)";
	return "   ";
}