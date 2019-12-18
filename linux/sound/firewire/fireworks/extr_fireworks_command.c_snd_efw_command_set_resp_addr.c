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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct snd_efw {int /*<<< orphan*/  resp_addr_changable; } ;
typedef  int /*<<< orphan*/  addr ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  EFC_CAT_HWCTL ; 
 int /*<<< orphan*/  EFC_CMD_HWINFO_SET_RESP_ADDR ; 
 int ENOSYS ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int efw_transaction (struct snd_efw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int snd_efw_command_set_resp_addr(struct snd_efw *efw,
				  u16 addr_high, u32 addr_low)
{
	__be32 addr[2];

	addr[0] = cpu_to_be32(addr_high);
	addr[1] = cpu_to_be32(addr_low);

	if (!efw->resp_addr_changable)
		return -ENOSYS;

	return efw_transaction(efw, EFC_CAT_HWCTL,
			       EFC_CMD_HWINFO_SET_RESP_ADDR,
			       addr, sizeof(addr), NULL, 0);
}