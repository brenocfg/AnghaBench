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
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  rijndael_decrypt (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
aes_cbc_decrypt(rijndael_ctx *ctx, uint8 *iva, uint8 *data, unsigned len)
{
	uint32	   *d = (uint32 *) data;
	unsigned	bs = 16;
	uint32		buf[4],
				iv[4];

	memcpy(iv, iva, bs);
	while (len >= bs)
	{
		buf[0] = d[0];
		buf[1] = d[1];
		buf[2] = d[2];
		buf[3] = d[3];

		rijndael_decrypt(ctx, buf, d);

		d[0] ^= iv[0];
		d[1] ^= iv[1];
		d[2] ^= iv[2];
		d[3] ^= iv[3];

		iv[0] = buf[0];
		iv[1] = buf[1];
		iv[2] = buf[2];
		iv[3] = buf[3];
		d += 4;
		len -= bs;
	}
}