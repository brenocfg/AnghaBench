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
struct gcov_info {int /*<<< orphan*/  head; } ;

/* Variables and functions */
 int /*<<< orphan*/  __list_del_entry (int /*<<< orphan*/ *) ; 

void gcov_info_unlink(struct gcov_info *prev, struct gcov_info *info)
{
	/* Generic code unlinks while iterating. */
	__list_del_entry(&info->head);
}