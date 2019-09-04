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

void __raid6_datap_recov_neon(int bytes, uint8_t *p, uint8_t *q, uint8_t *dq,
			      const uint8_t *qmul)
{
	uint8x16_t qm0 = vld1q_u8(qmul);
	uint8x16_t qm1 = vld1q_u8(qmul + 16);

	/*
	 * while (bytes--) {
	 *	*p++ ^= *dq = qmul[*q ^ *dq];
	 *	q++; dq++;
	 * }
	 */

	while (bytes) {
		uint8x16_t vx, vy;

		vx = veorq_u8(vld1q_u8(q), vld1q_u8(dq));

		vy = (uint8x16_t)vshrq_n_s16((int16x8_t)vx, 4);
		vx = vqtbl1q_u8(qm0, vandq_u8(vx, x0f));
		vy = vqtbl1q_u8(qm1, vandq_u8(vy, x0f));
		vx = veorq_u8(vx, vy);
		vy = veorq_u8(vx, vld1q_u8(p));

		vst1q_u8(dq, vx);
		vst1q_u8(p, vy);

		bytes -= 16;
		p += 16;
		q += 16;
		dq += 16;
	}
}