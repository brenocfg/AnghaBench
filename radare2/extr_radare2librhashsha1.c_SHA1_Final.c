#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int ut8 ;
struct TYPE_5__ {int sizeHi; int sizeLo; int lenW; int* H; } ;
typedef  TYPE_1__ R_SHA_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  SHA1_Init (TYPE_1__*) ; 
 int /*<<< orphan*/  SHA1_Update (TYPE_1__*,int*,int) ; 

void SHA1_Final(ut8 hashout[20], R_SHA_CTX *ctx) {
	ut8 pad0x80 = 0x80;
	ut8 pad0x00 = 0x00;
	ut8 padlen[8];
	int i;

	/* Pad with a binary 1 (e.g. 0x80), then zeroes, then length */
	padlen[0] = (ut8) ((ctx->sizeHi >> 24) & 255);
	padlen[1] = (ut8) ((ctx->sizeHi >> 16) & 255);
	padlen[2] = (ut8) ((ctx->sizeHi >> 8) & 255);
	padlen[3] = (ut8) ((ctx->sizeHi >> 0) & 255);
	padlen[4] = (ut8) ((ctx->sizeLo >> 24) & 255);
	padlen[5] = (ut8) ((ctx->sizeLo >> 16) & 255);
	padlen[6] = (ut8) ((ctx->sizeLo >> 8) & 255);
	padlen[7] = (ut8) ((ctx->sizeLo >> 0) & 255);

	SHA1_Update (ctx, &pad0x80, 1);
	while (ctx->lenW != 56) {
		SHA1_Update (ctx, &pad0x00, 1);
	}
	SHA1_Update (ctx, padlen, 8);

	/* Output hash */
	for (i = 0; i < 20; i++) {
		hashout[i] = (ut8) (ctx->H[i / 4] >> 24);
		ctx->H[i / 4] <<= 8;
	}

	/* Re-initialize the context (also zeroizes contents) */
	SHA1_Init (ctx);
}