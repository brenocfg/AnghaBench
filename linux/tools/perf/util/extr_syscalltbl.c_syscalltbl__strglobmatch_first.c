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
struct syscalltbl {int dummy; } ;

/* Variables and functions */
 int syscalltbl__strglobmatch_next (struct syscalltbl*,char const*,int*) ; 

int syscalltbl__strglobmatch_first(struct syscalltbl *tbl, const char *syscall_glob, int *idx)
{
	return syscalltbl__strglobmatch_next(tbl, syscall_glob, idx);
}