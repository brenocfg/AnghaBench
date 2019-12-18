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
 int /*<<< orphan*/  bf_block_size ; 
 int /*<<< orphan*/  bf_decrypt ; 
 int /*<<< orphan*/  bf_encrypt ; 
 int /*<<< orphan*/  bf_init ; 
 int /*<<< orphan*/  bf_iv_size ; 
 int /*<<< orphan*/  bf_key_size ; 
 int /*<<< orphan*/  intctx_free ; 
 int /*<<< orphan*/  memset (struct int_ctx*,int /*<<< orphan*/ ,int) ; 
 struct int_ctx* px_alloc (int) ; 

__attribute__((used)) static PX_Cipher *
bf_load(int mode)
{
	PX_Cipher  *c;
	struct int_ctx *cx;

	c = px_alloc(sizeof *c);
	memset(c, 0, sizeof *c);

	c->block_size = bf_block_size;
	c->key_size = bf_key_size;
	c->iv_size = bf_iv_size;
	c->init = bf_init;
	c->encrypt = bf_encrypt;
	c->decrypt = bf_decrypt;
	c->free = intctx_free;

	cx = px_alloc(sizeof *cx);
	memset(cx, 0, sizeof *cx);
	cx->mode = mode;
	c->ptr = cx;
	return c;
}