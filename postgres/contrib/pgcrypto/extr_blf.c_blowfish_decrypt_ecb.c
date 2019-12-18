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
typedef  int /*<<< orphan*/  BlowfishContext ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  GET_32BIT_MSB_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PUT_32BIT_MSB_FIRST (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blowfish_decrypt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
blowfish_decrypt_ecb(uint8 *blk, int len, BlowfishContext *ctx)
{
	uint32		xL,
				xR,
				out[2];

	Assert((len & 7) == 0);

	while (len > 0)
	{
		xL = GET_32BIT_MSB_FIRST(blk);
		xR = GET_32BIT_MSB_FIRST(blk + 4);
		blowfish_decrypt(xL, xR, out, ctx);
		PUT_32BIT_MSB_FIRST(blk, out[0]);
		PUT_32BIT_MSB_FIRST(blk + 4, out[1]);
		blk += 8;
		len -= 8;
	}
}