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
 int /*<<< orphan*/  __gang_check (int,int,int,int,int) ; 

void gang_check(void)
{
	__gang_check(1UL << 30, 128, 128, 35, 2);
	__gang_check(1UL << 31, 128, 128, 32, 32);
	__gang_check(1UL << 31, 128, 128, 32, 100);
	__gang_check(1UL << 31, 128, 128, 17, 7);
	__gang_check(0xffff0000UL, 0, 65536, 17, 7);
	__gang_check(0xfffffffeUL, 1, 1, 17, 7);
}