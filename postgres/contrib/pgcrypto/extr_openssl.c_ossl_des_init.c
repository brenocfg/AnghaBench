#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8 ;
struct TYPE_6__ {int klen; int /*<<< orphan*/  iv; int /*<<< orphan*/  key; } ;
struct TYPE_5__ {TYPE_2__* ptr; } ;
typedef  TYPE_1__ PX_Cipher ;
typedef  TYPE_2__ OSSLCipher ;

/* Variables and functions */
 unsigned int gen_ossl_block_size (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int
ossl_des_init(PX_Cipher *c, const uint8 *key, unsigned klen, const uint8 *iv)
{
	OSSLCipher *od = c->ptr;
	unsigned	bs = gen_ossl_block_size(c);

	od->klen = 8;
	memset(od->key, 0, 8);
	memcpy(od->key, key, klen > 8 ? 8 : klen);

	if (iv)
		memcpy(od->iv, iv, bs);
	else
		memset(od->iv, 0, bs);
	return 0;
}