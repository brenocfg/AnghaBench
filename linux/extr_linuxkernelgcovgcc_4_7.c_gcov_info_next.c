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
struct gcov_info {struct gcov_info* next; } ;

/* Variables and functions */
 struct gcov_info* gcov_info_head ; 

struct gcov_info *gcov_info_next(struct gcov_info *info)
{
	if (!info)
		return gcov_info_head;

	return info->next;
}