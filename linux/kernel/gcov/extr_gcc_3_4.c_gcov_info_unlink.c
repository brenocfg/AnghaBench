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
struct gcov_info {int /*<<< orphan*/  next; } ;

/* Variables and functions */
 int /*<<< orphan*/  gcov_info_head ; 

void gcov_info_unlink(struct gcov_info *prev, struct gcov_info *info)
{
	if (prev)
		prev->next = info->next;
	else
		gcov_info_head = info->next;
}