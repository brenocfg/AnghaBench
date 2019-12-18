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
typedef  int /*<<< orphan*/  uint8 ;
typedef  int /*<<< orphan*/  uint32 ;
typedef  int /*<<< orphan*/  rijndael_ctx ;

/* Variables and functions */
 int /*<<< orphan*/  rijndael_encrypt (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
aes_cbc_encrypt(rijndael_ctx *ctx, uint8 *iva, uint8 *data, unsigned len)
{
	uint32	   *iv = (uint32 *) iva;
	uint32	   *d = (uint32 *) data;
	unsigned	bs = 16;

	while (len >= bs)
	{
		d[0] ^= iv[0];
		d[1] ^= iv[1];
		d[2] ^= iv[2];
		d[3] ^= iv[3];

		rijndael_encrypt(ctx, d, d);

		iv = d;
		d += bs / 4;
		len -= bs;
	}
}