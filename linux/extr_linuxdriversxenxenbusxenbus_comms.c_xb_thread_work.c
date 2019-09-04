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
 scalar_t__ xb_data_to_read () ; 
 scalar_t__ xb_data_to_write () ; 

__attribute__((used)) static int xb_thread_work(void)
{
	return xb_data_to_read() || xb_data_to_write();
}