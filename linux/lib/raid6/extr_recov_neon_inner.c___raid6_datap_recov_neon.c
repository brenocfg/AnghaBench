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

void __raid6_datap_recov_neon(int bytes, uint8_t *p, uint8_t *q, uint8_t *dq,
			      const uint8_t *qmul)
{
	uint8x16_t qm0 = vld1q_u8(qmul);
	uint8x16_t qm1 = vld1q_u8(qmul + 16);
	uint8x16_t x0f = vdupq_n_u8(0x0f);

	/*
	 * while (bytes--) {
	 *	*p++ ^= *dq = qmul[*q ^ *dq];
	 *	q++; dq++;
	 * }
	 */

	while (bytes) {
		uint8x16_t vx, vy;

		vx = veorq_u8(vld1q_u8(q), vld1q_u8(dq));

		vy = vshrq_n_u8(vx, 4);
		vx = vqtbl1q_u8(qm0, vandq_u8(vx, x0f));
		vy = vqtbl1q_u8(qm1, vy);
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