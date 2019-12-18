#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  enum CRC_PRESETS { ____Placeholder_CRC_PRESETS } CRC_PRESETS ;
struct TYPE_5__ {int /*<<< orphan*/  xout; int /*<<< orphan*/  poly; int /*<<< orphan*/  reflect; int /*<<< orphan*/  size; int /*<<< orphan*/  crc; } ;
struct TYPE_4__ {int /*<<< orphan*/  xout; int /*<<< orphan*/  poly; int /*<<< orphan*/  reflect; int /*<<< orphan*/  size; int /*<<< orphan*/  crc; } ;
typedef  TYPE_1__ R_CRC_CTX ;

/* Variables and functions */
 TYPE_2__* crc_presets ; 

void crc_init_preset (R_CRC_CTX *ctx, enum CRC_PRESETS preset) {
	ctx->crc = crc_presets[preset].crc;
	ctx->size = crc_presets[preset].size;
	ctx->reflect = crc_presets[preset].reflect;
	ctx->poly = crc_presets[preset].poly;
	ctx->xout = crc_presets[preset].xout;
}