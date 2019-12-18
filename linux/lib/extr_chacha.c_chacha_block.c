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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;

/* Variables and functions */
 int ARRAY_SIZE (scalar_t__*) ; 
 int /*<<< orphan*/  chacha_permute (scalar_t__*,int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__*,int) ; 
 int /*<<< orphan*/  put_unaligned_le32 (scalar_t__,int /*<<< orphan*/ *) ; 

void chacha_block(u32 *state, u8 *stream, int nrounds)
{
	u32 x[16];
	int i;

	memcpy(x, state, 64);

	chacha_permute(x, nrounds);

	for (i = 0; i < ARRAY_SIZE(x); i++)
		put_unaligned_le32(x[i] + state[i], &stream[i * sizeof(u32)]);

	state[12]++;
}