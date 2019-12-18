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
struct TYPE_8__ {int alloc; int used; scalar_t__ sign; scalar_t__* dp; } ;
typedef  TYPE_1__ mp_int ;
typedef  scalar_t__ mp_digit ;

/* Variables and functions */
 int CHAR_BIT ; 
 int /*<<< orphan*/  MP_MASK ; 
 scalar_t__ MP_NEG ; 
 int MP_OKAY ; 
 void* MP_ZPOS ; 
 int mp_add_d (TYPE_1__*,scalar_t__,TYPE_1__*) ; 
 int /*<<< orphan*/  mp_clamp (TYPE_1__*) ; 
 int mp_grow (TYPE_1__*,int) ; 

int
mp_sub_d (mp_int * a, mp_digit b, mp_int * c)
{
  mp_digit *tmpa, *tmpc, mu;
  int       res, ix, oldused;

  /* grow c as required */
  if (c->alloc < a->used + 1) {
     if ((res = mp_grow(c, a->used + 1)) != MP_OKAY) {
        return res;
     }
  }

  /* if a is negative just do an unsigned
   * addition [with fudged signs]
   */
  if (a->sign == MP_NEG) {
     a->sign = MP_ZPOS;
     res     = mp_add_d(a, b, c);
     a->sign = c->sign = MP_NEG;
     return res;
  }

  /* setup regs */
  oldused = c->used;
  tmpa    = a->dp;
  tmpc    = c->dp;

  /* if a <= b simply fix the single digit */
  if ((a->used == 1 && a->dp[0] <= b) || a->used == 0) {
     if (a->used == 1) {
        *tmpc++ = b - *tmpa;
     } else {
        *tmpc++ = b;
     }
     ix      = 1;

     /* negative/1digit */
     c->sign = MP_NEG;
     c->used = 1;
  } else {
     /* positive/size */
     c->sign = MP_ZPOS;
     c->used = a->used;

     /* subtract first digit */
     *tmpc    = *tmpa++ - b;
     mu       = *tmpc >> (sizeof(mp_digit) * CHAR_BIT - 1);
     *tmpc++ &= MP_MASK;

     /* handle rest of the digits */
     for (ix = 1; ix < a->used; ix++) {
        *tmpc    = *tmpa++ - mu;
        mu       = *tmpc >> (sizeof(mp_digit) * CHAR_BIT - 1);
        *tmpc++ &= MP_MASK;
     }
  }

  /* zero excess digits */
  while (ix++ < oldused) {
     *tmpc++ = 0;
  }
  mp_clamp(c);
  return MP_OKAY;
}