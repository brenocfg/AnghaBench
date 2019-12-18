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
struct ctl_table_header {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mq_sysctl_root ; 
 struct ctl_table_header* register_sysctl_table (int /*<<< orphan*/ ) ; 

struct ctl_table_header *mq_register_sysctl_table(void)
{
	return register_sysctl_table(mq_sysctl_root);
}