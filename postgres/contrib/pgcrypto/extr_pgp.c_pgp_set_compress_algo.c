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
struct TYPE_3__ {int compress_algo; } ;
typedef  TYPE_1__ PGP_Context ;

/* Variables and functions */
#define  PGP_COMPR_BZIP2 131 
#define  PGP_COMPR_NONE 130 
#define  PGP_COMPR_ZIP 129 
#define  PGP_COMPR_ZLIB 128 
 int PXE_ARGUMENT_ERROR ; 

int
pgp_set_compress_algo(PGP_Context *ctx, int algo)
{
	switch (algo)
	{
		case PGP_COMPR_NONE:
		case PGP_COMPR_ZIP:
		case PGP_COMPR_ZLIB:
		case PGP_COMPR_BZIP2:
			ctx->compress_algo = algo;
			return 0;
	}
	return PXE_ARGUMENT_ERROR;
}