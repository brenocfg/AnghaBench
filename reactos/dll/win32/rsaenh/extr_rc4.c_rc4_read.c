#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned char x; unsigned char y; unsigned char* buf; } ;
struct TYPE_5__ {TYPE_1__ rc4; } ;
typedef  TYPE_2__ prng_state ;

/* Variables and functions */

unsigned long rc4_read(unsigned char *buf, unsigned long len, prng_state *prng)
{
   unsigned char x, y, *s, tmp;
   unsigned long n;

   n = len;
   x = prng->rc4.x;
   y = prng->rc4.y;
   s = prng->rc4.buf;
   while (len--) {
      x = (x + 1) & 255;
      y = (y + s[x]) & 255;
      tmp = s[x]; s[x] = s[y]; s[y] = tmp;
      tmp = (s[x] + s[y]) & 255;
      *buf++ ^= s[tmp];
   }
   prng->rc4.x = x;
   prng->rc4.y = y;
   return n;
}