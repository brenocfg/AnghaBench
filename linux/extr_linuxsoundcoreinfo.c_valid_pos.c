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
typedef  scalar_t__ ssize_t ;
typedef  long loff_t ;

/* Variables and functions */

__attribute__((used)) static bool valid_pos(loff_t pos, size_t count)
{
	if (pos < 0 || (long) pos != pos || (ssize_t) count < 0)
		return false;
	if ((unsigned long) pos + (unsigned long) count < (unsigned long) pos)
		return false;
	return true;
}