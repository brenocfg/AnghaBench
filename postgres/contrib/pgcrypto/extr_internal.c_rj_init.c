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
struct int_ctx {int keylen; int /*<<< orphan*/ * iv; int /*<<< orphan*/  keybuf; } ;
struct TYPE_3__ {scalar_t__ ptr; } ;
typedef  TYPE_1__ PX_Cipher ;

/* Variables and functions */
 int PXE_KEY_TOO_BIG ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int
rj_init(PX_Cipher *c, const uint8 *key, unsigned klen, const uint8 *iv)
{
	struct int_ctx *cx = (struct int_ctx *) c->ptr;

	if (klen <= 128 / 8)
		cx->keylen = 128 / 8;
	else if (klen <= 192 / 8)
		cx->keylen = 192 / 8;
	else if (klen <= 256 / 8)
		cx->keylen = 256 / 8;
	else
		return PXE_KEY_TOO_BIG;

	memcpy(&cx->keybuf, key, klen);

	if (iv)
		memcpy(cx->iv, iv, 128 / 8);

	return 0;
}