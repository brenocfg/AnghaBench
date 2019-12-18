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
struct user_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_modify_ldt ; 
 int errno ; 
 int syscall (int /*<<< orphan*/ ,int,struct user_desc*,unsigned long) ; 

__attribute__((used)) static int safe_modify_ldt(int func, struct user_desc *ptr,
			   unsigned long bytecount)
{
	int ret = syscall(SYS_modify_ldt, 0x11, ptr, bytecount);
	if (ret < -1)
		errno = -ret;
	return ret;
}