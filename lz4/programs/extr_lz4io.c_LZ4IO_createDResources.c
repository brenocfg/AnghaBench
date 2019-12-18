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
struct TYPE_4__ {int /*<<< orphan*/ * dstFile; void* dstBuffer; void* srcBuffer; void* dstBufferSize; void* srcBufferSize; int /*<<< orphan*/  dCtx; } ;
typedef  TYPE_1__ dRess_t ;
typedef  int /*<<< orphan*/  LZ4IO_prefs_t ;
typedef  int /*<<< orphan*/  LZ4F_errorCode_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXM_THROW (int,char*,...) ; 
 int /*<<< orphan*/  LZ4F_VERSION ; 
 int /*<<< orphan*/  LZ4F_createDecompressionContext (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LZ4F_getErrorName (int /*<<< orphan*/  const) ; 
 scalar_t__ LZ4F_isError (int /*<<< orphan*/  const) ; 
 void* LZ4IO_dBufferSize ; 
 int /*<<< orphan*/  LZ4IO_loadDDict (int /*<<< orphan*/ * const,TYPE_1__*) ; 
 void* malloc (void*) ; 

__attribute__((used)) static dRess_t LZ4IO_createDResources(LZ4IO_prefs_t* const prefs)
{
    dRess_t ress;

    /* init */
    LZ4F_errorCode_t const errorCode = LZ4F_createDecompressionContext(&ress.dCtx, LZ4F_VERSION);
    if (LZ4F_isError(errorCode)) EXM_THROW(60, "Can't create LZ4F context : %s", LZ4F_getErrorName(errorCode));

    /* Allocate Memory */
    ress.srcBufferSize = LZ4IO_dBufferSize;
    ress.srcBuffer = malloc(ress.srcBufferSize);
    ress.dstBufferSize = LZ4IO_dBufferSize;
    ress.dstBuffer = malloc(ress.dstBufferSize);
    if (!ress.srcBuffer || !ress.dstBuffer) EXM_THROW(61, "Allocation error : not enough memory");

    LZ4IO_loadDDict(prefs, &ress);

    ress.dstFile = NULL;
    return ress;
}