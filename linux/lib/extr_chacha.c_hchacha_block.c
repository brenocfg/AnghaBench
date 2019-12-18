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
typedef  int /*<<< orphan*/  const u32 ;

/* Variables and functions */
 int /*<<< orphan*/  chacha_permute (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int) ; 

void hchacha_block(const u32 *in, u32 *out, int nrounds)
{
	u32 x[16];

	memcpy(x, in, 64);

	chacha_permute(x, nrounds);

	memcpy(&out[0], &x[0], 16);
	memcpy(&out[4], &x[12], 16);
}