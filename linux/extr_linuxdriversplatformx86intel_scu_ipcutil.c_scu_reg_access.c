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
struct scu_ipc_data {unsigned int count; int /*<<< orphan*/  mask; int /*<<< orphan*/ * data; int /*<<< orphan*/ * addr; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTTY ; 
#define  INTE_SCU_IPC_REGISTER_READ 130 
#define  INTE_SCU_IPC_REGISTER_UPDATE 129 
#define  INTE_SCU_IPC_REGISTER_WRITE 128 
 int intel_scu_ipc_readv (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 
 int intel_scu_ipc_update_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int intel_scu_ipc_writev (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static int scu_reg_access(u32 cmd, struct scu_ipc_data  *data)
{
	unsigned int count = data->count;

	if (count == 0 || count == 3 || count > 4)
		return -EINVAL;

	switch (cmd) {
	case INTE_SCU_IPC_REGISTER_READ:
		return intel_scu_ipc_readv(data->addr, data->data, count);
	case INTE_SCU_IPC_REGISTER_WRITE:
		return intel_scu_ipc_writev(data->addr, data->data, count);
	case INTE_SCU_IPC_REGISTER_UPDATE:
		return intel_scu_ipc_update_register(data->addr[0],
						    data->data[0], data->mask);
	default:
		return -ENOTTY;
	}
}