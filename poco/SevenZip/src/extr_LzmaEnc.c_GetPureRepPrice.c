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
struct TYPE_3__ {int /*<<< orphan*/ * isRepG2; int /*<<< orphan*/ * isRepG1; int /*<<< orphan*/ * isRepG0; int /*<<< orphan*/ ** isRep0Long; } ;
typedef  TYPE_1__ CLzmaEnc ;

/* Variables and functions */
 size_t GET_PRICE (int /*<<< orphan*/ ,size_t) ; 
 size_t GET_PRICE_0 (int /*<<< orphan*/ ) ; 
 size_t GET_PRICE_1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static UInt32 GetPureRepPrice(CLzmaEnc *p, UInt32 repIndex, UInt32 state, UInt32 posState)
{
  UInt32 price;
  if (repIndex == 0)
  {
    price = GET_PRICE_0(p->isRepG0[state]);
    price += GET_PRICE_1(p->isRep0Long[state][posState]);
  }
  else
  {
    price = GET_PRICE_1(p->isRepG0[state]);
    if (repIndex == 1)
      price += GET_PRICE_0(p->isRepG1[state]);
    else
    {
      price += GET_PRICE_1(p->isRepG1[state]);
      price += GET_PRICE(p->isRepG2[state], repIndex - 2);
    }
  }
  return price;
}