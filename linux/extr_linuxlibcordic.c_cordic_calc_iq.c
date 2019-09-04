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
struct cordic_iq {unsigned int i; unsigned int q; } ;
typedef  int s32 ;

/* Variables and functions */
 unsigned int CORDIC_ANGLE_GEN ; 
 unsigned int CORDIC_NUM_ITER ; 
 int FIXED (int) ; 
 int FLOAT (int) ; 
 scalar_t__* arctan_table ; 

struct cordic_iq cordic_calc_iq(s32 theta)
{
	struct cordic_iq coord;
	s32 angle, valtmp;
	unsigned iter;
	int signx = 1;
	int signtheta;

	coord.i = CORDIC_ANGLE_GEN;
	coord.q = 0;
	angle = 0;

	theta = FIXED(theta);
	signtheta = (theta < 0) ? -1 : 1;
	theta = ((theta + FIXED(180) * signtheta) % FIXED(360)) -
		FIXED(180) * signtheta;

	if (FLOAT(theta) > 90) {
		theta -= FIXED(180);
		signx = -1;
	} else if (FLOAT(theta) < -90) {
		theta += FIXED(180);
		signx = -1;
	}

	for (iter = 0; iter < CORDIC_NUM_ITER; iter++) {
		if (theta > angle) {
			valtmp = coord.i - (coord.q >> iter);
			coord.q += (coord.i >> iter);
			angle += arctan_table[iter];
		} else {
			valtmp = coord.i + (coord.q >> iter);
			coord.q -= (coord.i >> iter);
			angle -= arctan_table[iter];
		}
		coord.i = valtmp;
	}

	coord.i *= signx;
	coord.q *= signx;
	return coord;
}