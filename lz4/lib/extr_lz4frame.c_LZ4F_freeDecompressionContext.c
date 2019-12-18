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
struct TYPE_4__ {struct TYPE_4__* tmpOutBuffer; struct TYPE_4__* tmpIn; scalar_t__ dStage; } ;
typedef  scalar_t__ LZ4F_errorCode_t ;
typedef  TYPE_1__ LZ4F_dctx ;

/* Variables and functions */
 int /*<<< orphan*/  FREEMEM (TYPE_1__*) ; 
 scalar_t__ LZ4F_OK_NoError ; 

LZ4F_errorCode_t LZ4F_freeDecompressionContext(LZ4F_dctx* dctx)
{
    LZ4F_errorCode_t result = LZ4F_OK_NoError;
    if (dctx != NULL) {   /* can accept NULL input, like free() */
      result = (LZ4F_errorCode_t)dctx->dStage;
      FREEMEM(dctx->tmpIn);
      FREEMEM(dctx->tmpOutBuffer);
      FREEMEM(dctx);
    }
    return result;
}