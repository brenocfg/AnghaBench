#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned int* W; unsigned int* H; } ;
typedef  TYPE_1__ R_SHA_CTX ;

/* Variables and functions */
 unsigned int SHA_ROT (unsigned int,int) ; 

__attribute__((used)) static void shaHashBlock(R_SHA_CTX *ctx) {
	int t;
	unsigned int A, B, C, D, E, TEMP;

	for (t = 16; t <= 79; t++) {
		ctx->W[t] =
			SHA_ROT (ctx->W[t - 3] ^ ctx->W[t - 8] ^ ctx->W[t - 14] ^ ctx->W[t - 16], 1);
	}

	A = ctx->H[0];
	B = ctx->H[1];
	C = ctx->H[2];
	D = ctx->H[3];
	E = ctx->H[4];

	for (t = 0; t <= 19; t++) {
		TEMP = SHA_ROT (A, 5) + (((C ^ D) & B) ^ D) + E + ctx->W[t] + 0x5a827999;
		E = D; D = C; C = SHA_ROT (B, 30); B = A; A = TEMP;
	}
	for (t = 20; t <= 39; t++) {
		TEMP = SHA_ROT (A, 5) + (B ^ C ^ D) + E + ctx->W[t] + 0x6ed9eba1;
		E = D; D = C; C = SHA_ROT (B, 30); B = A; A = TEMP;
	}
	for (t = 40; t <= 59; t++) {
		TEMP = SHA_ROT (A, 5) + ((B & C) | (D & (B | C))) + E + ctx->W[t] + 0x8f1bbcdc;
		E = D; D = C; C = SHA_ROT (B, 30); B = A; A = TEMP;
	}
	for (t = 60; t <= 79; t++) {
		TEMP = SHA_ROT (A, 5) + (B ^ C ^ D) + E + ctx->W[t] + 0xca62c1d6;
		E = D; D = C; C = SHA_ROT (B, 30); B = A; A = TEMP;
	}

	ctx->H[0] += A;
	ctx->H[1] += B;
	ctx->H[2] += C;
	ctx->H[3] += D;
	ctx->H[4] += E;
}