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
struct snd_efw_phys_meters {int dummy; } ;
struct snd_efw {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  EFC_CAT_HWINFO ; 
 int /*<<< orphan*/  EFC_CMD_HWINFO_GET_POLLED ; 
 int /*<<< orphan*/  be32_to_cpus (int /*<<< orphan*/ *) ; 
 int efw_transaction (struct snd_efw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int) ; 

int snd_efw_command_get_phys_meters(struct snd_efw *efw,
				    struct snd_efw_phys_meters *meters,
				    unsigned int len)
{
	u32 *buf = (u32 *)meters;
	unsigned int i;
	int err;

	err = efw_transaction(efw, EFC_CAT_HWINFO,
			      EFC_CMD_HWINFO_GET_POLLED,
			      NULL, 0, (__be32 *)meters, len);
	if (err >= 0)
		for (i = 0; i < len / sizeof(u32); i++)
			be32_to_cpus(&buf[i]);

	return err;
}