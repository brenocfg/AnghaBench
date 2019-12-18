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
struct TYPE_2__ {unsigned int version; scalar_t__ cStage; } ;
typedef  int /*<<< orphan*/  LZ4F_errorCode_t ;
typedef  scalar_t__ LZ4F_compressionContext_t ;
typedef  TYPE_1__ LZ4F_cctx_t ;

/* Variables and functions */
 scalar_t__ ALLOC_AND_ZERO (int) ; 
 int /*<<< orphan*/  LZ4F_ERROR_allocation_failed ; 
 int /*<<< orphan*/  LZ4F_OK_NoError ; 
 int /*<<< orphan*/  err0r (int /*<<< orphan*/ ) ; 

LZ4F_errorCode_t LZ4F_createCompressionContext(LZ4F_compressionContext_t* LZ4F_compressionContextPtr, unsigned version)
{
    LZ4F_cctx_t* const cctxPtr = (LZ4F_cctx_t*)ALLOC_AND_ZERO(sizeof(LZ4F_cctx_t));
    if (cctxPtr==NULL) return err0r(LZ4F_ERROR_allocation_failed);

    cctxPtr->version = version;
    cctxPtr->cStage = 0;   /* Next stage : init stream */

    *LZ4F_compressionContextPtr = (LZ4F_compressionContext_t)cctxPtr;

    return LZ4F_OK_NoError;
}