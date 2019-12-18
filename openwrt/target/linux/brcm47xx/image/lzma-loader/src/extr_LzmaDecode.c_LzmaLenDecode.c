#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  CRangeDecoder ;
typedef  int /*<<< orphan*/  CProb ;

/* Variables and functions */
 int LenChoice ; 
 int LenChoice2 ; 
 int LenHigh ; 
 int LenLow ; 
 int LenMid ; 
 scalar_t__ RangeDecoderBitDecode (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int RangeDecoderBitTreeDecode (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int kLenNumHighBits ; 
 int kLenNumLowBits ; 
 int kLenNumLowSymbols ; 
 int kLenNumMidBits ; 
 int kLenNumMidSymbols ; 

int LzmaLenDecode(CProb *p, CRangeDecoder *rd, int posState)
{
  if(RangeDecoderBitDecode(p + LenChoice, rd) == 0)
    return RangeDecoderBitTreeDecode(p + LenLow +
        (posState << kLenNumLowBits), kLenNumLowBits, rd);
  if(RangeDecoderBitDecode(p + LenChoice2, rd) == 0)
    return kLenNumLowSymbols + RangeDecoderBitTreeDecode(p + LenMid +
        (posState << kLenNumMidBits), kLenNumMidBits, rd);
  return kLenNumLowSymbols + kLenNumMidSymbols + 
      RangeDecoderBitTreeDecode(p + LenHigh, kLenNumHighBits, rd);
}