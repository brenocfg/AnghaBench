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
 int php_array_natural_general_compare (void const*,void const*,int) ; 

__attribute__((used)) static int php_array_reverse_natural_case_compare(const void *a, const void *b) /* {{{ */
{
	return php_array_natural_general_compare(b, a, 1);
}