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
typedef  int u32 ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ENOMEM ; 
#define  IPC_GLB_REPLY_BUSY 129 
#define  IPC_GLB_REPLY_OUT_OF_MEMORY 128 

__attribute__((used)) static int skl_ipc_set_reply_error_code(u32 reply)
{
	switch (reply) {
	case IPC_GLB_REPLY_OUT_OF_MEMORY:
		return -ENOMEM;

	case IPC_GLB_REPLY_BUSY:
		return -EBUSY;

	default:
		return -EINVAL;
	}
}