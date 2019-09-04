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
typedef  void* utcrc ;
typedef  int /*<<< orphan*/  ut32 ;
struct TYPE_3__ {int reflect; void* xout; void* poly; int /*<<< orphan*/  size; void* crc; } ;
typedef  TYPE_1__ R_CRC_CTX ;

/* Variables and functions */

void crc_init (R_CRC_CTX *ctx, utcrc crc, ut32 size, int reflect, utcrc poly, utcrc xout) {
	ctx->crc = crc;
	ctx->size = size;
	ctx->reflect = reflect;
	ctx->poly = poly;
	ctx->xout = xout;
}