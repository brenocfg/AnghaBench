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
struct smc_clc_msg_smcd {int dummy; } ;
struct smc_clc_msg_proposal {int /*<<< orphan*/  iparea_offset; } ;

/* Variables and functions */
 int ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct smc_clc_msg_smcd *
smc_get_clc_msg_smcd(struct smc_clc_msg_proposal *prop)
{
	if (ntohs(prop->iparea_offset) != sizeof(struct smc_clc_msg_smcd))
		return NULL;

	return (struct smc_clc_msg_smcd *)(prop + 1);
}