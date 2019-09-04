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
 int filename__read_ull_base (char const*,unsigned long long*,int) ; 

int filename__read_xll(const char *filename, unsigned long long *value)
{
	return filename__read_ull_base(filename, value, 16);
}