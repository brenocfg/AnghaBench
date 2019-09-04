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
struct syscall_arg {int /*<<< orphan*/  val; } ;

/* Variables and functions */
 size_t scnprintf (char*,size_t,char*,int /*<<< orphan*/ ) ; 

size_t syscall_arg__scnprintf_int(char *bf, size_t size, struct syscall_arg *arg)
{
	return scnprintf(bf, size, "%d", arg->val);
}