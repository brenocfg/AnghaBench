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
struct gcov_info {scalar_t__ stamp; } ;

/* Variables and functions */

int gcov_info_is_compatible(struct gcov_info *info1, struct gcov_info *info2)
{
	return (info1->stamp == info2->stamp);
}