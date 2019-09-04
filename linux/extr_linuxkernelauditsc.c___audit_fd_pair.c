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
struct audit_context {int* fds; } ;

/* Variables and functions */
 struct audit_context* audit_context () ; 

void __audit_fd_pair(int fd1, int fd2)
{
	struct audit_context *context = audit_context();
	context->fds[0] = fd1;
	context->fds[1] = fd2;
}