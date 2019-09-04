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
 int dup2 (int,int) ; 

__attribute__((used)) static bool terminal_dup2(int duplicate, int original)
{
	int ret;

	ret = dup2(duplicate, original);
	if (ret < 0)
		return false;

	return true;
}