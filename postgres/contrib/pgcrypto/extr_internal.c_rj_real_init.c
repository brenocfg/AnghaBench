#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  rj; } ;
struct int_ctx {int keylen; int /*<<< orphan*/  keybuf; TYPE_1__ ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  aes_set_key (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int
rj_real_init(struct int_ctx *cx, int dir)
{
	aes_set_key(&cx->ctx.rj, cx->keybuf, cx->keylen * 8, dir);
	return 0;
}