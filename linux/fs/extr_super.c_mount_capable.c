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
struct fs_context {int /*<<< orphan*/  user_ns; TYPE_1__* fs_type; } ;
struct TYPE_2__ {int fs_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int FS_USERNS_MOUNT ; 
 int capable (int /*<<< orphan*/ ) ; 
 int ns_capable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool mount_capable(struct fs_context *fc)
{
	if (!(fc->fs_type->fs_flags & FS_USERNS_MOUNT))
		return capable(CAP_SYS_ADMIN);
	else
		return ns_capable(fc->user_ns, CAP_SYS_ADMIN);
}