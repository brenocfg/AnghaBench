#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8 ;
struct TYPE_4__ {int /*<<< orphan*/  bf; } ;
struct int_ctx {TYPE_1__ ctx; } ;
struct TYPE_5__ {scalar_t__ ptr; } ;
typedef  TYPE_2__ PX_Cipher ;

/* Variables and functions */
 int /*<<< orphan*/  blowfish_setiv (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  blowfish_setkey (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned int) ; 

__attribute__((used)) static int
bf_init(PX_Cipher *c, const uint8 *key, unsigned klen, const uint8 *iv)
{
	struct int_ctx *cx = (struct int_ctx *) c->ptr;

	blowfish_setkey(&cx->ctx.bf, key, klen);
	if (iv)
		blowfish_setiv(&cx->ctx.bf, iv);

	return 0;
}