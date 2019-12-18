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
struct TYPE_3__ {int /*<<< orphan*/ * cipher; } ;
typedef  TYPE_1__ PX_Combo ;
typedef  int /*<<< orphan*/  PX_Cipher ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/ * px_alloc (unsigned int) ; 
 int px_cipher_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ *) ; 
 unsigned int px_cipher_iv_size (int /*<<< orphan*/ *) ; 
 unsigned int px_cipher_key_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  px_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
combo_init(PX_Combo *cx, const uint8 *key, unsigned klen,
		   const uint8 *iv, unsigned ivlen)
{
	int			err;
	unsigned	ks,
				ivs;
	PX_Cipher  *c = cx->cipher;
	uint8	   *ivbuf = NULL;
	uint8	   *keybuf;

	ks = px_cipher_key_size(c);

	ivs = px_cipher_iv_size(c);
	if (ivs > 0)
	{
		ivbuf = px_alloc(ivs);
		memset(ivbuf, 0, ivs);
		if (ivlen > ivs)
			memcpy(ivbuf, iv, ivs);
		else
			memcpy(ivbuf, iv, ivlen);
	}

	if (klen > ks)
		klen = ks;
	keybuf = px_alloc(ks);
	memset(keybuf, 0, ks);
	memcpy(keybuf, key, klen);

	err = px_cipher_init(c, keybuf, klen, ivbuf);

	if (ivbuf)
		px_free(ivbuf);
	px_free(keybuf);

	return err;
}