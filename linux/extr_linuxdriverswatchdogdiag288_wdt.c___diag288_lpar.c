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
 int /*<<< orphan*/  DIAG_STAT_X288 ; 
 int __diag288 (unsigned int,unsigned int,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  diag_stat_inc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __diag288_lpar(unsigned int func, unsigned int timeout,
			  unsigned long action)
{
	diag_stat_inc(DIAG_STAT_X288);
	return __diag288(func, timeout, action, 0);
}