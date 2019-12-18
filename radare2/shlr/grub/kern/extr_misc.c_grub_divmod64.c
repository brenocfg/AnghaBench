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
typedef  int grub_uint64_t ;
typedef  int grub_uint32_t ;

/* Variables and functions */

grub_uint64_t
grub_divmod64 (grub_uint64_t n, grub_uint32_t d, grub_uint32_t *r)
{
  /* This algorithm is typically implemented by hardware. The idea
     is to get the highest bit in N, 64 times, by keeping
     upper(N * 2^i) = upper((Q * 10 + M) * 2^i), where upper
     represents the high 64 bits in 128-bits space.  */
  unsigned bits = 64;
  unsigned long long q = 0;
  unsigned m = 0;

  /* Skip the slow computation if 32-bit arithmetic is possible.  */
  if (n < 0xffffffff)
    {
      if (r)
	*r = ((grub_uint32_t) n) % d;

      return ((grub_uint32_t) n) / d;
    }

  while (bits--)
    {
      m <<= 1;

      if (n & (1ULL << 63))
	m |= 1;

      q <<= 1;
      n <<= 1;

      if (m >= d)
	{
	  q |= 1;
	  m -= d;
	}
    }

  if (r)
    *r = m;

  return q;
}