#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8 ;
typedef  int /*<<< orphan*/  mix_data_t ;
struct TYPE_4__ {scalar_t__ resync; } ;
typedef  TYPE_1__ PGP_CFB ;

/* Variables and functions */
 int cfb_process (TYPE_1__*,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mix_encrypt_normal ; 
 int /*<<< orphan*/  mix_encrypt_resync ; 

int
pgp_cfb_encrypt(PGP_CFB *ctx, const uint8 *data, int len, uint8 *dst)
{
	mix_data_t	mix = ctx->resync ? mix_encrypt_resync : mix_encrypt_normal;

	return cfb_process(ctx, data, len, dst, mix);
}