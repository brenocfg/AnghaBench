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
 int /*<<< orphan*/  rijndael_set_key (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int,int) ; 

void
aes_set_key(rijndael_ctx *ctx, const uint8 *key, unsigned keybits, int enc)
{
	uint32	   *k;

	k = (uint32 *) key;
	rijndael_set_key(ctx, k, keybits, enc);
}