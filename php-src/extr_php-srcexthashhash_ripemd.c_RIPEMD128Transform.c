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
typedef  int /*<<< orphan*/  x ;
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 scalar_t__ F0 (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ F1 (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ F2 (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ F3 (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ K (int) ; 
 scalar_t__ KK (int) ; 
 size_t* R ; 
 int /*<<< orphan*/  RIPEMDDecode (scalar_t__*,unsigned char const*,int) ; 
 scalar_t__ ROLS (int,scalar_t__) ; 
 scalar_t__ ROLSS (int,scalar_t__) ; 
 size_t* RR ; 
 int /*<<< orphan*/  ZEND_SECURE_ZERO (scalar_t__*,int) ; 

__attribute__((used)) static void RIPEMD128Transform(uint32_t state[4], const unsigned char block[64])
{
	uint32_t a  = state[0], b  = state[1], c  = state[2], d  = state[3];
	uint32_t aa = state[0], bb = state[1], cc = state[2], dd = state[3];
	uint32_t tmp, x[16];
	int j;

	RIPEMDDecode(x, block, 64);

	for(j = 0; j < 16; j++) {
		tmp = ROLS( j, a  + F0(b,  c,  d)  + x[R[j]]  + K(j));
		a = d; d = c; c = b; b = tmp;
		tmp = ROLSS(j, aa + F3(bb, cc, dd) + x[RR[j]] + KK(j));
		aa = dd; dd = cc; cc = bb; bb = tmp;
	}

	for(j = 16; j < 32; j++) {
		tmp = ROLS( j, a  + F1(b,  c,  d)  + x[R[j]]  + K(j));
		a = d; d = c; c = b; b = tmp;
		tmp = ROLSS(j, aa + F2(bb, cc, dd) + x[RR[j]] + KK(j));
		aa = dd; dd = cc; cc = bb; bb = tmp;
	}

	for(j = 32; j < 48; j++) {
		tmp = ROLS( j, a  + F2(b,  c,  d)  + x[R[j]]  + K(j));
		a = d; d = c; c = b; b = tmp;
		tmp = ROLSS(j, aa + F1(bb, cc, dd) + x[RR[j]] + KK(j));
		aa = dd; dd = cc; cc = bb; bb = tmp;
	}

	for(j = 48; j < 64; j++) {
		tmp = ROLS( j, a  + F3(b,  c,  d)  + x[R[j]]  + K(j));
		a = d; d = c; c = b; b = tmp;
		tmp = ROLSS(j, aa + F0(bb, cc, dd) + x[RR[j]] + KK(j));
		aa = dd; dd = cc; cc = bb; bb = tmp;
	}

	tmp = state[1] + c + dd;
	state[1] = state[2] + d + aa;
	state[2] = state[3] + a + bb;
	state[3] = state[0] + b + cc;
	state[0] = tmp;

	tmp = 0;
	ZEND_SECURE_ZERO(x, sizeof(x));
}