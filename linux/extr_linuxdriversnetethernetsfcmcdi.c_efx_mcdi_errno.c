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

/* Variables and functions */
 int EACCES ; 
 int EADDRINUSE ; 
 int EAGAIN ; 
 int EALREADY ; 
 int EBUSY ; 
 int EDEADLK ; 
 int EINTR ; 
 int EINVAL ; 
 int ENOBUFS ; 
 int ENOENT ; 
 int ENOSPC ; 
 int ENOSYS ; 
 int EOPNOTSUPP ; 
 int EPERM ; 
 int EPROTO ; 
 int ETIME ; 
#define  MC_CMD_ERR_ALLOC_FAIL 142 
#define  MC_CMD_ERR_EACCES 141 
#define  MC_CMD_ERR_EAGAIN 140 
#define  MC_CMD_ERR_EALREADY 139 
#define  MC_CMD_ERR_EBUSY 138 
#define  MC_CMD_ERR_EDEADLK 137 
#define  MC_CMD_ERR_EINTR 136 
#define  MC_CMD_ERR_EINVAL 135 
#define  MC_CMD_ERR_ENOENT 134 
#define  MC_CMD_ERR_ENOSPC 133 
#define  MC_CMD_ERR_ENOSYS 132 
#define  MC_CMD_ERR_ENOTSUP 131 
#define  MC_CMD_ERR_EPERM 130 
#define  MC_CMD_ERR_ETIME 129 
#define  MC_CMD_ERR_MAC_EXIST 128 

__attribute__((used)) static int efx_mcdi_errno(unsigned int mcdi_err)
{
	switch (mcdi_err) {
	case 0:
		return 0;
#define TRANSLATE_ERROR(name)					\
	case MC_CMD_ERR_ ## name:				\
		return -name;
	TRANSLATE_ERROR(EPERM);
	TRANSLATE_ERROR(ENOENT);
	TRANSLATE_ERROR(EINTR);
	TRANSLATE_ERROR(EAGAIN);
	TRANSLATE_ERROR(EACCES);
	TRANSLATE_ERROR(EBUSY);
	TRANSLATE_ERROR(EINVAL);
	TRANSLATE_ERROR(EDEADLK);
	TRANSLATE_ERROR(ENOSYS);
	TRANSLATE_ERROR(ETIME);
	TRANSLATE_ERROR(EALREADY);
	TRANSLATE_ERROR(ENOSPC);
#undef TRANSLATE_ERROR
	case MC_CMD_ERR_ENOTSUP:
		return -EOPNOTSUPP;
	case MC_CMD_ERR_ALLOC_FAIL:
		return -ENOBUFS;
	case MC_CMD_ERR_MAC_EXIST:
		return -EADDRINUSE;
	default:
		return -EPROTO;
	}
}