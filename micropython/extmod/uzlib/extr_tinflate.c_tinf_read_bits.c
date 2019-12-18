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
typedef  int /*<<< orphan*/  TINF_DATA ;

/* Variables and functions */
 scalar_t__ tinf_getbit (int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned int tinf_read_bits(TINF_DATA *d, int num, int base)
{
   unsigned int val = 0;

   /* read num bits */
   if (num)
   {
      unsigned int limit = 1 << (num);
      unsigned int mask;

      for (mask = 1; mask < limit; mask *= 2)
         if (tinf_getbit(d)) val += mask;
   }

   return val + base;
}