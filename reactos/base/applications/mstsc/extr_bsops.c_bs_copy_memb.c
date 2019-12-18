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

/* Variables and functions */

void
bs_copy_memb(char * d, char * s, int n)
{
  d = (d + n) - 1;
  s = (s + n) - 1;
  while (n & (~7))
  {
    *(d--) = *(s--);
    *(d--) = *(s--);
    *(d--) = *(s--);
    *(d--) = *(s--);
    *(d--) = *(s--);
    *(d--) = *(s--);
    *(d--) = *(s--);
    *(d--) = *(s--);
    n = n - 8;
  }
  while (n > 0)
  {
    *(d--) = *(s--);
    n--;
  }
}