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
struct efx_nic {TYPE_1__* type; } ;
struct TYPE_2__ {int mcdi_max_ver; } ;

/* Variables and functions */
 int EINVAL ; 
 int EMSGSIZE ; 
 size_t MCDI_CTL_SDU_LEN_MAX_V1 ; 
 size_t MCDI_CTL_SDU_LEN_MAX_V2 ; 
 unsigned int MC_CMD_CMD_SPACE_ESCAPE_7 ; 

__attribute__((used)) static int
efx_mcdi_check_supported(struct efx_nic *efx, unsigned int cmd, size_t inlen)
{
	if (efx->type->mcdi_max_ver < 0 ||
	     (efx->type->mcdi_max_ver < 2 &&
	      cmd > MC_CMD_CMD_SPACE_ESCAPE_7))
		return -EINVAL;

	if (inlen > MCDI_CTL_SDU_LEN_MAX_V2 ||
	    (efx->type->mcdi_max_ver < 2 &&
	     inlen > MCDI_CTL_SDU_LEN_MAX_V1))
		return -EMSGSIZE;

	return 0;
}