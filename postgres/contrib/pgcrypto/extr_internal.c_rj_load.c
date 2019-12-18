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
struct int_ctx {int mode; struct int_ctx* ptr; int /*<<< orphan*/  free; int /*<<< orphan*/  decrypt; int /*<<< orphan*/  encrypt; int /*<<< orphan*/  init; int /*<<< orphan*/  iv_size; int /*<<< orphan*/  key_size; int /*<<< orphan*/  block_size; } ;
typedef  struct int_ctx PX_Cipher ;

/* Variables and functions */
 int /*<<< orphan*/  intctx_free ; 
 int /*<<< orphan*/  memset (struct int_ctx*,int /*<<< orphan*/ ,int) ; 
 struct int_ctx* px_alloc (int) ; 
 int /*<<< orphan*/  rj_block_size ; 
 int /*<<< orphan*/  rj_decrypt ; 
 int /*<<< orphan*/  rj_encrypt ; 
 int /*<<< orphan*/  rj_init ; 
 int /*<<< orphan*/  rj_iv_size ; 
 int /*<<< orphan*/  rj_key_size ; 

__attribute__((used)) static PX_Cipher *
rj_load(int mode)
{
	PX_Cipher  *c;
	struct int_ctx *cx;

	c = px_alloc(sizeof *c);
	memset(c, 0, sizeof *c);

	c->block_size = rj_block_size;
	c->key_size = rj_key_size;
	c->iv_size = rj_iv_size;
	c->init = rj_init;
	c->encrypt = rj_encrypt;
	c->decrypt = rj_decrypt;
	c->free = intctx_free;

	cx = px_alloc(sizeof *cx);
	memset(cx, 0, sizeof *cx);
	cx->mode = mode;

	c->ptr = cx;
	return c;
}