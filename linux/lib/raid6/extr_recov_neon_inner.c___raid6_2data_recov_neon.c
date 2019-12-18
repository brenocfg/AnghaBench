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
typedef  int /*<<< orphan*/  uint8x16_t ;
typedef  int /*<<< orphan*/  const uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  vandq_u8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdupq_n_u8 (int) ; 
 int /*<<< orphan*/  veorq_u8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vld1q_u8 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  vqtbl1q_u8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vshrq_n_u8 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vst1q_u8 (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

void __raid6_2data_recov_neon(int bytes, uint8_t *p, uint8_t *q, uint8_t *dp,
			      uint8_t *dq, const uint8_t *pbmul,
			      const uint8_t *qmul)
{
	uint8x16_t pm0 = vld1q_u8(pbmul);
	uint8x16_t pm1 = vld1q_u8(pbmul + 16);
	uint8x16_t qm0 = vld1q_u8(qmul);
	uint8x16_t qm1 = vld1q_u8(qmul + 16);
	uint8x16_t x0f = vdupq_n_u8(0x0f);

	/*
	 * while ( bytes-- ) {
	 *	uint8_t px, qx, db;
	 *
	 *	px    = *p ^ *dp;
	 *	qx    = qmul[*q ^ *dq];
	 *	*dq++ = db = pbmul[px] ^ qx;
	 *	*dp++ = db ^ px;
	 *	p++; q++;
	 * }
	 */

	while (bytes) {
		uint8x16_t vx, vy, px, qx, db;

		px = veorq_u8(vld1q_u8(p), vld1q_u8(dp));
		vx = veorq_u8(vld1q_u8(q), vld1q_u8(dq));

		vy = vshrq_n_u8(vx, 4);
		vx = vqtbl1q_u8(qm0, vandq_u8(vx, x0f));
		vy = vqtbl1q_u8(qm1, vy);
		qx = veorq_u8(vx, vy);

		vy = vshrq_n_u8(px, 4);
		vx = vqtbl1q_u8(pm0, vandq_u8(px, x0f));
		vy = vqtbl1q_u8(pm1, vy);
		vx = veorq_u8(vx, vy);
		db = veorq_u8(vx, qx);

		vst1q_u8(dq, db);
		vst1q_u8(dp, veorq_u8(db, px));

		bytes -= 16;
		p += 16;
		q += 16;
		dp += 16;
		dq += 16;
	}
}