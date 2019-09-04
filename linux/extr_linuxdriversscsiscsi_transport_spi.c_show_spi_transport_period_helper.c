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
typedef  int ssize_t ;

/* Variables and functions */
 int period_to_str (char*,int) ; 

__attribute__((used)) static ssize_t
show_spi_transport_period_helper(char *buf, int period)
{
	int len = period_to_str(buf, period);
	buf[len++] = '\n';
	buf[len] = '\0';
	return len;
}