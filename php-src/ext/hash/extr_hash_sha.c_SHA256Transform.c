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
 scalar_t__ SHA256_F0 (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ SHA256_F1 (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ SHA256_F2 (scalar_t__) ; 
 scalar_t__ SHA256_F3 (scalar_t__) ; 
 scalar_t__ SHA256_F4 (scalar_t__) ; 
 scalar_t__ SHA256_F5 (scalar_t__) ; 
 scalar_t__* SHA256_K ; 
 int /*<<< orphan*/  SHADecode32 (scalar_t__*,unsigned char const*,int) ; 
 int /*<<< orphan*/  ZEND_SECURE_ZERO (unsigned char*,int) ; 

__attribute__((used)) static void SHA256Transform(uint32_t state[8], const unsigned char block[64])
{
	uint32_t a = state[0], b = state[1], c = state[2], d = state[3];
	uint32_t e = state[4], f = state[5], g = state[6], h = state[7];
	uint32_t x[16], T1, T2, W[64];
	int i;

	SHADecode32(x, block, 64);

	/* Schedule */
	for(i = 0; i < 16; i++) {
		W[i] = x[i];
	}
	for(i = 16; i < 64; i++) {
		W[i] = SHA256_F5(W[i-2]) + W[i-7] + SHA256_F4(W[i-15]) + W[i-16];
	}

	for (i = 0; i < 64; i++) {
		T1 = h + SHA256_F3(e) + SHA256_F0(e,f,g) + SHA256_K[i] + W[i];
		T2 = SHA256_F2(a) + SHA256_F1(a,b,c);
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