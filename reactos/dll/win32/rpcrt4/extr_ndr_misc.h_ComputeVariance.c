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
typedef  scalar_t__ ULONG_PTR ;
typedef  scalar_t__ ULONG ;
struct TYPE_4__ {scalar_t__ ActualCount; scalar_t__ Offset; } ;
typedef  TYPE_1__* PMIDL_STUB_MESSAGE ;
typedef  int /*<<< orphan*/  PFORMAT_STRING ;

/* Variables and functions */
 int /*<<< orphan*/  ComputeConformanceOrVariance (TYPE_1__*,unsigned char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__*) ; 

__attribute__((used)) static inline PFORMAT_STRING ComputeVariance(PMIDL_STUB_MESSAGE pStubMsg, unsigned char *pMemory, PFORMAT_STRING pFormat, ULONG def)
{
    PFORMAT_STRING ret;
    ULONG_PTR ActualCount = pStubMsg->ActualCount;

    pStubMsg->Offset = 0;
    ret = ComputeConformanceOrVariance(pStubMsg, pMemory, pFormat, def, &ActualCount);
    pStubMsg->ActualCount = (ULONG)ActualCount;
    return ret;
}