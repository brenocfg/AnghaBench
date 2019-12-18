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
struct TYPE_3__ {scalar_t__ dictSize; int /*<<< orphan*/ * dict; int /*<<< orphan*/  dStage; } ;
typedef  TYPE_1__ LZ4F_dctx ;

/* Variables and functions */
 int /*<<< orphan*/  dstage_getFrameHeader ; 

void LZ4F_resetDecompressionContext(LZ4F_dctx* dctx)
{
    dctx->dStage = dstage_getFrameHeader;
    dctx->dict = NULL;
    dctx->dictSize = 0;
}