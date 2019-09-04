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
 scalar_t__ IS_ERR (void const*) ; 
 long PTR_ERR (void const*) ; 

long libbpf_get_error(const void *ptr)
{
	if (IS_ERR(ptr))
		return PTR_ERR(ptr);
	return 0;
}