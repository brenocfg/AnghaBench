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
typedef  int /*<<< orphan*/  uint8 ;
struct TYPE_3__ {int sym_key_len; int /*<<< orphan*/  const* sym_key; } ;
typedef  TYPE_1__ PGP_Context ;

/* Variables and functions */
 int PXE_ARGUMENT_ERROR ; 

int
pgp_set_symkey(PGP_Context *ctx, const uint8 *key, int len)
{
	if (key == NULL || len < 1)
		return PXE_ARGUMENT_ERROR;
	ctx->sym_key = key;
	ctx->sym_key_len = len;
	return 0;
}