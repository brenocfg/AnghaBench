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
 unsigned long LONG_MAX ; 
 void* xa_mk_value (unsigned long) ; 

__attribute__((used)) static void *xa_mk_index(unsigned long index)
{
	return xa_mk_value(index & LONG_MAX);
}