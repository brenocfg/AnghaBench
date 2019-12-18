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
struct TYPE_3__ {int s2k_mode; } ;
typedef  TYPE_1__ PGP_Context ;

/* Variables and functions */
#define  PGP_S2K_ISALTED 130 
#define  PGP_S2K_SALTED 129 
#define  PGP_S2K_SIMPLE 128 
 int PXE_ARGUMENT_ERROR ; 
 int PXE_OK ; 

int
pgp_set_s2k_mode(PGP_Context *ctx, int mode)
{
	int			err = PXE_OK;

	switch (mode)
	{
		case PGP_S2K_SIMPLE:
		case PGP_S2K_SALTED:
		case PGP_S2K_ISALTED:
			ctx->s2k_mode = mode;
			break;
		default:
			err = PXE_ARGUMENT_ERROR;
			break;
	}
	return err;
}