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
struct TYPE_2__ {struct crypto_skcipher** data; } ;
struct key_preparsed_payload {int datalen; TYPE_1__ payload; int /*<<< orphan*/  data; } ;
struct crypto_skcipher {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  CRYPTO_ALG_ASYNC ; 
 int EINVAL ; 
 scalar_t__ IS_ERR (struct crypto_skcipher*) ; 
 int PTR_ERR (struct crypto_skcipher*) ; 
 int /*<<< orphan*/  _enter (char*,int) ; 
 int /*<<< orphan*/  _leave (char*,...) ; 
 struct crypto_skcipher* crypto_alloc_skcipher (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ crypto_skcipher_setkey (struct crypto_skcipher*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (struct crypto_skcipher**,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int rxrpc_preparse_s(struct key_preparsed_payload *prep)
{
	struct crypto_skcipher *ci;

	_enter("%zu", prep->datalen);

	if (prep->datalen != 8)
		return -EINVAL;

	memcpy(&prep->payload.data[2], prep->data, 8);

	ci = crypto_alloc_skcipher("pcbc(des)", 0, CRYPTO_ALG_ASYNC);
	if (IS_ERR(ci)) {
		_leave(" = %ld", PTR_ERR(ci));
		return PTR_ERR(ci);
	}

	if (crypto_skcipher_setkey(ci, prep->data, 8) < 0)
		BUG();

	prep->payload.data[0] = ci;
	_leave(" = 0");
	return 0;
}