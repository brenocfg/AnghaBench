#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ s2k_mode; int s2k_count; } ;
typedef  TYPE_1__ PGP_Context ;

/* Variables and functions */
 scalar_t__ PGP_S2K_ISALTED ; 
 int PXE_ARGUMENT_ERROR ; 
 int PXE_OK ; 

int
pgp_set_s2k_count(PGP_Context *ctx, int count)
{
	if (ctx->s2k_mode == PGP_S2K_ISALTED && count >= 1024 && count <= 65011712)
	{
		ctx->s2k_count = count;
		return PXE_OK;
	}
	return PXE_ARGUMENT_ERROR;
}