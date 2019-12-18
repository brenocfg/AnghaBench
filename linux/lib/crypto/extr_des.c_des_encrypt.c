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
typedef  int /*<<< orphan*/  u32 ;
struct des_ctx {int /*<<< orphan*/ * expkey; } ;

/* Variables and functions */
 int /*<<< orphan*/  FP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ROUND (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  get_unaligned_le32 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  put_unaligned_le32 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void des_encrypt(const struct des_ctx *ctx, u8 *dst, const u8 *src)
{
	const u32 *K = ctx->expkey;
	u32 L, R, A, B;
	int i;

	L = get_unaligned_le32(src);
	R = get_unaligned_le32(src + 4);

	IP(L, R, A);
	for (i = 0; i < 8; i++) {
		ROUND(L, R, A, B, K, 2);
		ROUND(R, L, A, B, K, 2);
	}
	FP(R, L, A);

	put_unaligned_le32(R, dst);
	put_unaligned_le32(L, dst + 4);
}