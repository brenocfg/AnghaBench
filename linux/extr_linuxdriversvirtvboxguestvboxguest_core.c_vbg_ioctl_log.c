#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  msg; } ;
struct TYPE_6__ {TYPE_2__ in; } ;
struct TYPE_4__ {int size_out; int size_in; } ;
struct vbg_ioctl_log {TYPE_3__ u; TYPE_1__ hdr; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  vbg_info (char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vbg_ioctl_log(struct vbg_ioctl_log *log)
{
	if (log->hdr.size_out != sizeof(log->hdr))
		return -EINVAL;

	vbg_info("%.*s", (int)(log->hdr.size_in - sizeof(log->hdr)),
		 log->u.in.msg);

	return 0;
}