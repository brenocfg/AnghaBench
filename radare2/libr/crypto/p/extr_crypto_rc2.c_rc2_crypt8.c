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
typedef  int ut8 ;
typedef  int ut16 ;
struct rc2_state {scalar_t__* ekey; } ;

/* Variables and functions */

__attribute__((used)) static void rc2_crypt8(struct rc2_state *state, const ut8 *inbuf, ut8 *outbuf) {
	int i;
	ut16 x76, x54, x32, x10;

	x76 = (inbuf[7] << 8) | inbuf[6];
	x54 = (inbuf[5] << 8) | inbuf[4];
	x32 = (inbuf[3] << 8) | inbuf[2];
	x10 = (inbuf[1] << 8) | inbuf[0];

	for (i = 0; i < 16; i++) {
		x10 += ((x32 & ~x76) + (x54 & x76)) + state->ekey[4 * i + 0];
		x10 = (x10 << 1) + (x10 >> 15 & 1);

		x32 += ((x54 & ~x10) + (x76 & x10)) + state->ekey[4 * i + 1];
		x32 = (x32 << 2) + (x32 >> 14 & 3);

		x54 += ((x76 & ~x32) + (x10 & x32)) + state->ekey[4 * i + 2];
		x54 = (x54 << 3) + (x54 >> 13 & 7);

		x76 += ((x10 & ~x54) + (x32 & x54)) + state->ekey[4 * i + 3];
		x76 = (x76 << 5) + (x76 >> 11 & 31);

		if (i == 4 || i == 10) {
			x10 += state->ekey[x76 & 63];
			x32 += state->ekey[x10 & 63];
			x54 += state->ekey[x32 & 63];
			x76 += state->ekey[x54 & 63];
		}
	}

	outbuf[0] = (ut8) x10;
	outbuf[1] = (ut8) (x10 >> 8);
	outbuf[2] = (ut8) x32;
	outbuf[3] = (ut8) (x32 >> 8);
	outbuf[4] = (ut8) x54;
	outbuf[5] = (ut8) (x54 >> 8);
	outbuf[6] = (ut8) x76;
	outbuf[7] = (ut8) (x76 >> 8);
}