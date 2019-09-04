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
struct syscalltbl {int /*<<< orphan*/  audit_machine; } ;

/* Variables and functions */
 int audit_name_to_syscall (char const*,int /*<<< orphan*/ ) ; 

int syscalltbl__id(struct syscalltbl *tbl, const char *name)
{
	return audit_name_to_syscall(name, tbl->audit_machine);
}