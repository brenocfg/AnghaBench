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
struct pn533_target_felica {scalar_t__ opcode; } ;

/* Variables and functions */
 scalar_t__ PN533_FELICA_OPC_SENSF_RES ; 

__attribute__((used)) static bool pn533_target_felica_is_valid(struct pn533_target_felica *felica,
							int target_data_len)
{
	if (target_data_len < sizeof(struct pn533_target_felica))
		return false;

	if (felica->opcode != PN533_FELICA_OPC_SENSF_RES)
		return false;

	return true;
}