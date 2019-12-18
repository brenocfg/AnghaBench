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
typedef  int UInt32 ;
typedef  int SizeT ;
typedef  int Byte ;

/* Variables and functions */
 scalar_t__ Test86MSByte (int) ; 
 int /*<<< orphan*/ * kMaskToAllowedStatus ; 
 int* kMaskToBitNumber ; 

SizeT x86_Convert(Byte *data, SizeT size, UInt32 ip, UInt32 *state, int encoding)
{
  SizeT bufferPos = 0, prevPosT;
  UInt32 prevMask = *state & 0x7;
  if (size < 5)
    return 0;
  ip += 5;
  prevPosT = (SizeT)0 - 1;

  for (;;)
  {
    Byte *p = data + bufferPos;
    Byte *limit = data + size - 4;
    for (; p < limit; p++)
      if ((*p & 0xFE) == 0xE8)
        break;
    bufferPos = (SizeT)(p - data);
    if (p >= limit)
      break;
    prevPosT = bufferPos - prevPosT;
    if (prevPosT > 3)
      prevMask = 0;
    else
    {
      prevMask = (prevMask << ((int)prevPosT - 1)) & 0x7;
      if (prevMask != 0)
      {
        Byte b = p[4 - kMaskToBitNumber[prevMask]];
        if (!kMaskToAllowedStatus[prevMask] || Test86MSByte(b))
        {
          prevPosT = bufferPos;
          prevMask = ((prevMask << 1) & 0x7) | 1;
          bufferPos++;
          continue;
        }
      }
    }
    prevPosT = bufferPos;

    if (Test86MSByte(p[4]))
    {
      UInt32 src = ((UInt32)p[4] << 24) | ((UInt32)p[3] << 16) | ((UInt32)p[2] << 8) | ((UInt32)p[1]);
      UInt32 dest;
      for (;;)
      {
        Byte b;
        int index;
        if (encoding)
          dest = (ip + (UInt32)bufferPos) + src;
        else
          dest = src - (ip + (UInt32)bufferPos);
        if (prevMask == 0)
          break;
        index = kMaskToBitNumber[prevMask] * 8;
        b = (Byte)(dest >> (24 - index));
        if (!Test86MSByte(b))
          break;
        src = dest ^ ((1 << (32 - index)) - 1);
      }
      p[4] = (Byte)(~(((dest >> 24) & 1) - 1));
      p[3] = (Byte)(dest >> 16);
      p[2] = (Byte)(dest >> 8);
      p[1] = (Byte)dest;
      bufferPos += 5;
    }
    else
    {
      prevMask = ((prevMask << 1) & 0x7) | 1;
      bufferPos++;
    }
  }
  prevPosT = bufferPos - prevPosT;
  *state = ((prevPosT > 3) ? 0 : ((prevMask << ((int)prevPosT - 1)) & 0x7));
  return bufferPos;
}