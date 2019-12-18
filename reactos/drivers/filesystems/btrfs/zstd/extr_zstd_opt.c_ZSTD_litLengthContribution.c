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
struct TYPE_3__ {scalar_t__ priceType; size_t const* litLengthFreq; } ;
typedef  TYPE_1__ optState_t ;
typedef  size_t U32 ;

/* Variables and functions */
 int BITCOST_MULTIPLIER ; 
 int* LL_bits ; 
 int MAX (int /*<<< orphan*/ ,int const) ; 
 int WEIGHT (size_t const,int) ; 
 size_t ZSTD_LLcode (size_t const) ; 
 scalar_t__ zop_predef ; 

__attribute__((used)) static int ZSTD_litLengthContribution(U32 const litLength, const optState_t* const optPtr, int optLevel)
{
    if (optPtr->priceType >= zop_predef) return WEIGHT(litLength, optLevel);

    /* dynamic statistics */
    {   U32 const llCode = ZSTD_LLcode(litLength);
        int const contribution = (LL_bits[llCode] * BITCOST_MULTIPLIER)
                               + WEIGHT(optPtr->litLengthFreq[0], optLevel)   /* note: log2litLengthSum cancel out */
                               - WEIGHT(optPtr->litLengthFreq[llCode], optLevel);
#if 1
        return contribution;
#else
        return MAX(0, contribution); /* sometimes better, sometimes not ... */
#endif
    }
}