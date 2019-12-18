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
typedef  int int64_t ;

/* Variables and functions */
 int TSC_ADJUST_VALUE ; 
 int /*<<< orphan*/  printf (char*,int,int,int) ; 

__attribute__((used)) static void report(int64_t val)
{
	printf("IA32_TSC_ADJUST is %ld (%lld * TSC_ADJUST_VALUE + %lld).\n",
	       val, val / TSC_ADJUST_VALUE, val % TSC_ADJUST_VALUE);
}