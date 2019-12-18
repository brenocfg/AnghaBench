#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int alloc; int used; int /*<<< orphan*/ * dp; } ;
typedef  TYPE_1__ mp_int ;

/* Variables and functions */
 int MP_OKAY ; 
 int /*<<< orphan*/  mp_clamp (TYPE_1__*) ; 
 int mp_grow (TYPE_1__*,int) ; 
 int mp_mul_2d (TYPE_1__*,int,TYPE_1__*) ; 
 int /*<<< orphan*/  mp_zero (TYPE_1__*) ; 

int
mp_read_unsigned_bin (mp_int * a, const unsigned char *b, int c)
{
  int     res;

  /* make sure there are at least two digits */
  if (a->alloc < 2) {
     if ((res = mp_grow(a, 2)) != MP_OKAY) {
        return res;
     }
  }

  /* zero the int */
  mp_zero (a);

  /* read the bytes in */
  while (c-- > 0) {
    if ((res = mp_mul_2d (a, 8, a)) != MP_OKAY) {
      return res;
    }

    a->dp[0] |= *b++;
    a->used += 1;
  }
  mp_clamp (a);
  return MP_OKAY;
}