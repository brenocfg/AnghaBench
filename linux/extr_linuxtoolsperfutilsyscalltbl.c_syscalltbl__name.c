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
 char const* audit_syscall_to_name (int,int /*<<< orphan*/ ) ; 

const char *syscalltbl__name(const struct syscalltbl *tbl, int id)
{
	return audit_syscall_to_name(id, tbl->audit_machine);
}