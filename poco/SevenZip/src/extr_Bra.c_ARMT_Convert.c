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

SizeT ARMT_Convert(Byte *data, SizeT size, UInt32 ip, int encoding)
{
  SizeT i;
  if (size < 4)
    return 0;
  size -= 4;
  ip += 4;
  for (i = 0; i <= size; i += 2)
  {
    if ((data[i + 1] & 0xF8) == 0xF0 &&
        (data[i + 3] & 0xF8) == 0xF8)
    {
      UInt32 dest;
      UInt32 src =
        (((UInt32)data[i + 1] & 0x7) << 19) |
        ((UInt32)data[i + 0] << 11) |
        (((UInt32)data[i + 3] & 0x7) << 8) |
        (data[i + 2]);
      
      src <<= 1;
      if (encoding)
        dest = ip + (UInt32)i + src;
      else
        dest = src - (ip + (UInt32)i);
      dest >>= 1;
      
      data[i + 1] = (Byte)(0xF0 | ((dest >> 19) & 0x7));
      data[i + 0] = (Byte)(dest >> 11);
      data[i + 3] = (Byte)(0xF8 | ((dest >> 8) & 0x7));
      data[i + 2] = (Byte)dest;
      i += 2;
    }
  }
  return i;
}