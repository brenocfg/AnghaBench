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
typedef  int /*<<< orphan*/  u8 ;
struct des_ctx {int /*<<< orphan*/  expkey; } ;

/* Variables and functions */
 unsigned int DES_KEY_SIZE ; 
 int EINVAL ; 
 int ENOKEY ; 
 scalar_t__ des_ekey (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

int des_expand_key(struct des_ctx *ctx, const u8 *key, unsigned int keylen)
{
	if (keylen != DES_KEY_SIZE)
		return -EINVAL;

	return des_ekey(ctx->expkey, key) ? 0 : -ENOKEY;
}