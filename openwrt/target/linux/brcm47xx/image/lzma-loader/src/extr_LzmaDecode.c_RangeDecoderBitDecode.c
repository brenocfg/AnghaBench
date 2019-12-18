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
typedef  scalar_t__ UInt32 ;
struct TYPE_3__ {scalar_t__ Range; scalar_t__ Code; } ;
typedef  TYPE_1__ CRangeDecoder ;
typedef  scalar_t__ CProb ;

/* Variables and functions */
 int ReadByte ; 
 scalar_t__ kBitModelTotal ; 
 scalar_t__ kNumBitModelTotalBits ; 
 scalar_t__ kNumMoveBits ; 
 scalar_t__ kTopValue ; 

int RangeDecoderBitDecode(CProb *prob, CRangeDecoder *rd)
{
  UInt32 bound = (rd->Range >> kNumBitModelTotalBits) * *prob;
  if (rd->Code < bound)
  {
    rd->Range = bound;
    *prob += (kBitModelTotal - *prob) >> kNumMoveBits;
    if (rd->Range < kTopValue)
    {
      rd->Code = (rd->Code << 8) | ReadByte;
      rd->Range <<= 8;
    }
    return 0;
  }
  else
  {
    rd->Range -= bound;
    rd->Code -= bound;
    *prob -= (*prob) >> kNumMoveBits;
    if (rd->Range < kTopValue)
    {
      rd->Code = (rd->Code << 8) | ReadByte;
      rd->Range <<= 8;
    }
    return 1;
  }
}