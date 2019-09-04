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
typedef  scalar_t__ uint8x16_t ;
typedef  int /*<<< orphan*/  const uint8_t ;
typedef  int /*<<< orphan*/  int16x8_t ;

/* Variables and functions */
 int /*<<< orphan*/  vandq_u8 (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ veorq_u8 (scalar_t__,scalar_t__) ; 
 scalar_t__ vld1q_u8 (int /*<<< orphan*/  const*) ; 
 scalar_t__ vqtbl1q_u8 (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ vshrq_n_s16 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vst1q_u8 (int /*<<< orphan*/  const*,scalar_t__) ; 
 int /*<<< orphan*/  x0f ; 

void __raid6_2data_recov_neon(int bytes, uint8_t *p, uint8_t *q, uint8_t *dp,
			      uint8_t *dq, const uint8_t *pbmul,
			      const uint8_t *qmul)
{
	uint8x16_t pm0 = vld1q_u8(pbmul);
	uint8x16_t pm1 = vld1q_u8(pbmul + 16);
	uint8x16_t qm0 = vld1q_u8(qmul);
	uint8x16_t qm1 = vld1q_u8(qmul + 16);

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

		vy = (uint8x16_t)vshrq_n_s16((int16x8_t)vx, 4);
		vx = vqtbl1q_u8(qm0, vandq_u8(vx, x0f));
		vy = vqtbl1q_u8(qm1, vandq_u8(vy, x0f));
		qx = veorq_u8(vx, vy);

		vy = (uint8x16_t)vshrq_n_s16((int16x8_t)px, 4);
		vx = vqtbl1q_u8(pm0, vandq_u8(px, x0f));
		vy = vqtbl1q_u8(pm1, vandq_u8(vy, x0f));
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