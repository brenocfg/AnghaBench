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
typedef  int /*<<< orphan*/ * ioctl_fn ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ **) ; 
#define  autofs_dev_ioctl_askumount 141 
#define  autofs_dev_ioctl_catatonic 140 
#define  autofs_dev_ioctl_closemount 139 
#define  autofs_dev_ioctl_expire 138 
#define  autofs_dev_ioctl_fail 137 
#define  autofs_dev_ioctl_ismountpoint 136 
#define  autofs_dev_ioctl_openmount 135 
#define  autofs_dev_ioctl_protosubver 134 
#define  autofs_dev_ioctl_protover 133 
#define  autofs_dev_ioctl_ready 132 
#define  autofs_dev_ioctl_requester 131 
#define  autofs_dev_ioctl_setpipefd 130 
#define  autofs_dev_ioctl_timeout 129 
#define  autofs_dev_ioctl_version 128 
 unsigned int cmd_idx (unsigned int) ; 

__attribute__((used)) static ioctl_fn lookup_dev_ioctl(unsigned int cmd)
{
	static ioctl_fn _ioctls[] = {
		autofs_dev_ioctl_version,
		autofs_dev_ioctl_protover,
		autofs_dev_ioctl_protosubver,
		autofs_dev_ioctl_openmount,
		autofs_dev_ioctl_closemount,
		autofs_dev_ioctl_ready,
		autofs_dev_ioctl_fail,
		autofs_dev_ioctl_setpipefd,
		autofs_dev_ioctl_catatonic,
		autofs_dev_ioctl_timeout,
		autofs_dev_ioctl_requester,
		autofs_dev_ioctl_expire,
		autofs_dev_ioctl_askumount,
		autofs_dev_ioctl_ismountpoint,
	};
	unsigned int idx = cmd_idx(cmd);

	return (idx >= ARRAY_SIZE(_ioctls)) ? NULL : _ioctls[idx];
}