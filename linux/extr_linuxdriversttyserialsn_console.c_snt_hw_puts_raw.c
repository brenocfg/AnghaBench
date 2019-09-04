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
 int ia64_sn_console_putb (char const*,int) ; 

__attribute__((used)) static int snt_hw_puts_raw(const char *s, int len)
{
	/* this will call the PROM and not return until this is done */
	return ia64_sn_console_putb(s, len);
}