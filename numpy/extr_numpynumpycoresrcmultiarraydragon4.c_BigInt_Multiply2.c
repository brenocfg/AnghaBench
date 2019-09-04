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
typedef  int npy_uint32 ;
struct TYPE_4__ {int* blocks; int length; } ;
typedef  TYPE_1__ BigInt ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_ASSERT (int) ; 
 scalar_t__ c_BigInt_MaxBlocks ; 

__attribute__((used)) static void
BigInt_Multiply2(BigInt *result, const BigInt *in)
{
    /* shift all the blocks by one */
    npy_uint32 carry = 0;

    npy_uint32 *resultCur = result->blocks;
    const npy_uint32 *pLhsCur = in->blocks;
    const npy_uint32 *pLhsEnd = in->blocks + in->length;
    for ( ; pLhsCur != pLhsEnd; ++pLhsCur, ++resultCur) {
        npy_uint32 cur = *pLhsCur;
        *resultCur = (cur << 1) | carry;
        carry = cur >> 31;
    }

    if (carry != 0) {
        /* grow the array */
        DEBUG_ASSERT(in->length + 1 <= c_BigInt_MaxBlocks);
        *resultCur = carry;
        result->length = in->length + 1;
    }
    else {
        result->length = in->length;
    }
}