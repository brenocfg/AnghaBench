#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ctl_table_header {TYPE_1__* ctl_table; } ;
struct TYPE_2__ {scalar_t__ child; } ;

/* Variables and functions */
 scalar_t__ sysctl_mount_point ; 

__attribute__((used)) static bool is_empty_dir(struct ctl_table_header *head)
{
	return head->ctl_table[0].child == sysctl_mount_point;
}