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
typedef  unsigned int uint8 ;
struct TYPE_3__ {scalar_t__ padding; int /*<<< orphan*/ * cipher; } ;
typedef  TYPE_1__ PX_Combo ;
typedef  int /*<<< orphan*/  PX_Cipher ;

/* Variables and functions */
 int PXE_DECRYPT_FAILED ; 
 int PXE_NOTBLOCKSIZE ; 
 unsigned int px_cipher_block_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  px_cipher_decrypt (int /*<<< orphan*/ *,unsigned int const*,unsigned int,unsigned int*) ; 

__attribute__((used)) static int
combo_decrypt(PX_Combo *cx, const uint8 *data, unsigned dlen,
			  uint8 *res, unsigned *rlen)
{
	unsigned	bs,
				i,
				pad;
	unsigned	pad_ok;

	PX_Cipher  *c = cx->cipher;

	/* decide whether zero-length input is allowed */
	if (dlen == 0)
	{
		/* with padding, empty ciphertext is not allowed */
		if (cx->padding)
			return PXE_DECRYPT_FAILED;

		/* without padding, report empty result */
		*rlen = 0;
		return 0;
	}

	bs = px_cipher_block_size(c);
	if (bs > 1 && (dlen % bs) != 0)
		goto block_error;

	/* decrypt */
	*rlen = dlen;
	px_cipher_decrypt(c, data, dlen, res);

	/* unpad */
	if (bs > 1 && cx->padding)
	{
		pad = res[*rlen - 1];
		pad_ok = 0;
		if (pad > 0 && pad <= bs && pad <= *rlen)
		{
			pad_ok = 1;
			for (i = *rlen - pad; i < *rlen; i++)
				if (res[i] != pad)
				{
					pad_ok = 0;
					break;
				}
		}

		if (pad_ok)
			*rlen -= pad;
	}

	return 0;

block_error:
	return PXE_NOTBLOCKSIZE;
}