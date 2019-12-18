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
typedef  size_t UInt32 ;
struct TYPE_3__ {scalar_t__ high; scalar_t__ mid; scalar_t__ low; int /*<<< orphan*/  choice2; int /*<<< orphan*/  choice; } ;
typedef  TYPE_1__ CLenEnc ;

/* Variables and functions */
 size_t GET_PRICE_0a (int /*<<< orphan*/ ) ; 
 size_t GET_PRICE_1a (int /*<<< orphan*/ ) ; 
 size_t RcTree_GetPrice (scalar_t__,size_t,size_t,size_t*) ; 
 size_t kLenNumHighBits ; 
 size_t kLenNumLowBits ; 
 size_t kLenNumLowSymbols ; 
 size_t kLenNumMidBits ; 
 size_t kLenNumMidSymbols ; 

__attribute__((used)) static void LenEnc_SetPrices(CLenEnc *p, UInt32 posState, UInt32 numSymbols, UInt32 *prices, UInt32 *ProbPrices)
{
  UInt32 a0 = GET_PRICE_0a(p->choice);
  UInt32 a1 = GET_PRICE_1a(p->choice);
  UInt32 b0 = a1 + GET_PRICE_0a(p->choice2);
  UInt32 b1 = a1 + GET_PRICE_1a(p->choice2);
  UInt32 i = 0;
  for (i = 0; i < kLenNumLowSymbols; i++)
  {
    if (i >= numSymbols)
      return;
    prices[i] = a0 + RcTree_GetPrice(p->low + (posState << kLenNumLowBits), kLenNumLowBits, i, ProbPrices);
  }
  for (; i < kLenNumLowSymbols + kLenNumMidSymbols; i++)
  {
    if (i >= numSymbols)
      return;
    prices[i] = b0 + RcTree_GetPrice(p->mid + (posState << kLenNumMidBits), kLenNumMidBits, i - kLenNumLowSymbols, ProbPrices);
  }
  for (; i < numSymbols; i++)
    prices[i] = b1 + RcTree_GetPrice(p->high, kLenNumHighBits, i - kLenNumLowSymbols - kLenNumMidSymbols, ProbPrices);
}