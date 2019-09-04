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
 size_t roundup (size_t,int) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static size_t intel_pt_filter_bytes(const char *filter)
{
	size_t len = filter ? strlen(filter) : 0;

	return len ? roundup(len + 1, 8) : 0;
}