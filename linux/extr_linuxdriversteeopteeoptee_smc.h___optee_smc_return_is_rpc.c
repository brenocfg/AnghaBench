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
 int OPTEE_SMC_RETURN_RPC_PREFIX ; 
 int OPTEE_SMC_RETURN_RPC_PREFIX_MASK ; 
 int OPTEE_SMC_RETURN_UNKNOWN_FUNCTION ; 

__attribute__((used)) static inline bool __optee_smc_return_is_rpc(u32 ret)
{
	return ret != OPTEE_SMC_RETURN_UNKNOWN_FUNCTION &&
	       (ret & OPTEE_SMC_RETURN_RPC_PREFIX_MASK) ==
			OPTEE_SMC_RETURN_RPC_PREFIX;
}