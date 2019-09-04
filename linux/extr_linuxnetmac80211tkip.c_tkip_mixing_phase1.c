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
typedef  int u32 ;
typedef  int u16 ;
struct tkip_ctx {int* p1k; int p1k_iv32; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int PHASE1_LOOP_COUNT ; 
 int /*<<< orphan*/  TKIP_STATE_PHASE1_DONE ; 
 int get_unaligned_le16 (int /*<<< orphan*/  const*) ; 
 scalar_t__ tkipS (int) ; 

__attribute__((used)) static void tkip_mixing_phase1(const u8 *tk, struct tkip_ctx *ctx,
			       const u8 *ta, u32 tsc_IV32)
{
	int i, j;
	u16 *p1k = ctx->p1k;

	p1k[0] = tsc_IV32 & 0xFFFF;
	p1k[1] = tsc_IV32 >> 16;
	p1k[2] = get_unaligned_le16(ta + 0);
	p1k[3] = get_unaligned_le16(ta + 2);
	p1k[4] = get_unaligned_le16(ta + 4);

	for (i = 0; i < PHASE1_LOOP_COUNT; i++) {
		j = 2 * (i & 1);
		p1k[0] += tkipS(p1k[4] ^ get_unaligned_le16(tk + 0 + j));
		p1k[1] += tkipS(p1k[0] ^ get_unaligned_le16(tk + 4 + j));
		p1k[2] += tkipS(p1k[1] ^ get_unaligned_le16(tk + 8 + j));
		p1k[3] += tkipS(p1k[2] ^ get_unaligned_le16(tk + 12 + j));
		p1k[4] += tkipS(p1k[3] ^ get_unaligned_le16(tk + 0 + j)) + i;
	}
	ctx->state = TKIP_STATE_PHASE1_DONE;
	ctx->p1k_iv32 = tsc_IV32;
}