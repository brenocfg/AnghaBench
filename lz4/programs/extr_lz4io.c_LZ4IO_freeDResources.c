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
struct TYPE_3__ {int /*<<< orphan*/  dictBuffer; int /*<<< orphan*/  dstBuffer; int /*<<< orphan*/  srcBuffer; int /*<<< orphan*/  dCtx; } ;
typedef  TYPE_1__ dRess_t ;
typedef  int /*<<< orphan*/  LZ4F_errorCode_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXM_THROW (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LZ4F_freeDecompressionContext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LZ4F_getErrorName (int /*<<< orphan*/ ) ; 
 scalar_t__ LZ4F_isError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void LZ4IO_freeDResources(dRess_t ress)
{
    LZ4F_errorCode_t errorCode = LZ4F_freeDecompressionContext(ress.dCtx);
    if (LZ4F_isError(errorCode)) EXM_THROW(69, "Error : can't free LZ4F context resource : %s", LZ4F_getErrorName(errorCode));
    free(ress.srcBuffer);
    free(ress.dstBuffer);
    free(ress.dictBuffer);
}