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
typedef  scalar_t__ uint64_t ;

/* Variables and functions */
 scalar_t__ SHA512_F0 (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ SHA512_F1 (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ SHA512_F2 (scalar_t__) ; 
 scalar_t__ SHA512_F3 (scalar_t__) ; 
 scalar_t__ SHA512_F4 (scalar_t__) ; 
 scalar_t__ SHA512_F5 (scalar_t__) ; 
 scalar_t__* SHA512_K ; 
 int /*<<< orphan*/  SHADecode64 (scalar_t__*,unsigned char const*,int) ; 
 int /*<<< orphan*/  ZEND_SECURE_ZERO (unsigned char*,int) ; 

__attribute__((used)) static void SHA512Transform(uint64_t state[8], const unsigned char block[128])
{
	uint64_t a = state[0], b = state[1], c = state[2], d = state[3];
	uint64_t e = state[4], f = state[5], g = state[6], h = state[7];
	uint64_t x[16], T1, T2, W[80];
	int i;

	SHADecode64(x, block, 128);

	/* Schedule */
	for(i = 0; i < 16; i++) {
		W[i] = x[i];
	}
	for(i = 16; i < 80; i++) {
		W[i] = SHA512_F5(W[i-2]) + W[i-7] + SHA512_F4(W[i-15]) + W[i-16];
	}

	for (i = 0; i < 80; i++) {
		T1 = h + SHA512_F3(e) + SHA512_F0(e,f,g) + SHA512_K[i] + W[i];
		T2 = SHA512_F2(a) + SHA512_F1(a,b,c);
		h = g; g = f; f = e; e = d + T1;
		d = c; c = b; b = a; a = T1 + T2;
	}

	state[0] += a;
	state[1] += b;
	state[2] += c;
	state[3] += d;
	state[4] += e;
	state[5] += f;
	state[6] += g;
	state[7] += h;

	/* Zeroize sensitive information. */
	ZEND_SECURE_ZERO((unsigned char*) x, sizeof(x));
}