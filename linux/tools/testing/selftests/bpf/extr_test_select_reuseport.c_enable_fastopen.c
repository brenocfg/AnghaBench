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
 int /*<<< orphan*/  TCP_FO_SYSCTL ; 
 int read_int_sysctl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_int_sysctl (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void enable_fastopen(void)
{
	int fo;

	fo = read_int_sysctl(TCP_FO_SYSCTL);
	write_int_sysctl(TCP_FO_SYSCTL, fo | 7);
}