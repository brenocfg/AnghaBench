#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ut8 ;
struct TYPE_4__ {int* W; int lenW; int sizeLo; int sizeHi; } ;
typedef  TYPE_1__ R_SHA_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  shaHashBlock (TYPE_1__*) ; 

void SHA1_Update(R_SHA_CTX *ctx, const void *_dataIn, int len) {
	const ut8 *dataIn = _dataIn;
	int i;

	// Read the data into W and process blocks as they get full
	for (i = 0; i < len; i++) {
		ctx->W[ctx->lenW / 4] <<= 8;
		ctx->W[ctx->lenW / 4] |= (unsigned int) dataIn[i];
		if ((++ctx->lenW) % 64 == 0) {
			shaHashBlock (ctx);
			ctx->lenW = 0;
		}
		ctx->sizeLo += 8;
		ctx->sizeHi += (ctx->sizeLo < 8);
	}
}