#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ tmpBuff; scalar_t__ lz4CtxPtr; } ;
typedef  int /*<<< orphan*/  LZ4F_errorCode_t ;
typedef  scalar_t__ LZ4F_compressionContext_t ;
typedef  TYPE_1__ LZ4F_cctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  FREEMEM (scalar_t__) ; 
 int /*<<< orphan*/  LZ4F_OK_NoError ; 

LZ4F_errorCode_t LZ4F_freeCompressionContext(LZ4F_compressionContext_t LZ4F_compressionContext)
{
    LZ4F_cctx_t* const cctxPtr = (LZ4F_cctx_t*)LZ4F_compressionContext;

    if (cctxPtr != NULL) {  /* support free on NULL */
       FREEMEM(cctxPtr->lz4CtxPtr);  /* works because LZ4_streamHC_t and LZ4_stream_t are simple POD types */
       FREEMEM(cctxPtr->tmpBuff);
       FREEMEM(LZ4F_compressionContext);
    }

    return LZ4F_OK_NoError;
}