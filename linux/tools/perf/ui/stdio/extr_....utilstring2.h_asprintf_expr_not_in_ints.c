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
 char* asprintf_expr_inout_ints (char const*,int,size_t,int*) ; 

__attribute__((used)) static inline char *asprintf_expr_not_in_ints(const char *var, size_t nints, int *ints)
{
	return asprintf_expr_inout_ints(var, false, nints, ints);
}