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
struct TYPE_3__ {int /*<<< orphan*/  ctx; int /*<<< orphan*/ * cdict; int /*<<< orphan*/  dstBuffer; int /*<<< orphan*/  srcBuffer; } ;
typedef  TYPE_1__ cRess_t ;
typedef  int /*<<< orphan*/  LZ4F_errorCode_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXM_THROW (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LZ4F_freeCDict (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LZ4F_freeCompressionContext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LZ4F_getErrorName (int /*<<< orphan*/  const) ; 
 scalar_t__ LZ4F_isError (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void LZ4IO_freeCResources(cRess_t ress)
{
    free(ress.srcBuffer);
    free(ress.dstBuffer);

    LZ4F_freeCDict(ress.cdict);
    ress.cdict = NULL;

    { LZ4F_errorCode_t const errorCode = LZ4F_freeCompressionContext(ress.ctx);
      if (LZ4F_isError(errorCode)) EXM_THROW(38, "Error : can't free LZ4F context resource : %s", LZ4F_getErrorName(errorCode)); }
}