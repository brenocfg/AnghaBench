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
struct TYPE_2__ {int fd; int flags; } ;
struct audit_context {int /*<<< orphan*/  type; TYPE_1__ mmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_MMAP ; 
 struct audit_context* audit_context () ; 

void __audit_mmap_fd(int fd, int flags)
{
	struct audit_context *context = audit_context();
	context->mmap.fd = fd;
	context->mmap.flags = flags;
	context->type = AUDIT_MMAP;
}