#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_5__ {int /*<<< orphan*/  tfm; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  SHASH_DESC_ON_STACK (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  barrier_data (int /*<<< orphan*/ *) ; 
 int crypto_shash_update (TYPE_1__*,void const*,unsigned int) ; 
 TYPE_1__* shash ; 
 scalar_t__ shash_desc_ctx (TYPE_1__*) ; 
 int /*<<< orphan*/  tfm ; 

u32 crc32c(u32 crc, const void *address, unsigned int length)
{
	SHASH_DESC_ON_STACK(shash, tfm);
	u32 ret, *ctx = (u32 *)shash_desc_ctx(shash);
	int err;

	shash->tfm = tfm;
	*ctx = crc;

	err = crypto_shash_update(shash, address, length);
	BUG_ON(err);

	ret = *ctx;
	barrier_data(ctx);
	return ret;
}