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
typedef  int /*<<< orphan*/  PushFilter ;
typedef  int /*<<< orphan*/  PGP_Context ;

/* Variables and functions */
 int PXE_PGP_UNSUPPORTED_COMPR ; 

int
pgp_compress_filter(PushFilter **res, PGP_Context *ctx, PushFilter *dst)
{
	return PXE_PGP_UNSUPPORTED_COMPR;
}