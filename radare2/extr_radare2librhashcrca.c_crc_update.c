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
typedef  int utcrc ;
typedef  int ut8 ;
typedef  int ut32 ;
struct TYPE_3__ {int crc; int size; int poly; scalar_t__ reflect; } ;
typedef  TYPE_1__ R_CRC_CTX ;

/* Variables and functions */

void crc_update (R_CRC_CTX *ctx, const ut8 *data, ut32 sz) {
	utcrc crc, d;
	int i, j;

	crc = ctx->crc;
	for (i = 0; i < sz; i++) {
		d = data[i];
		if (ctx->reflect) {
			for (j = 0; j < 4; j++) {
				if (((d >> j) ^ (d >> (7 - j))) & 1) {
					d ^= (1 << j) ^ (1 << (7 - j));
				}
			}
		}
		crc ^= d << (ctx->size - 8);
		for (j = 0; j < 8; j++) {
			crc = ((crc >> (ctx->size - 1)) & 1? ctx->poly: 0) ^ (crc << 1);
		}
	}
	ctx->crc = crc;
}