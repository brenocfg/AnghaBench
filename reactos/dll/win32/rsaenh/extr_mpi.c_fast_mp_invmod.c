#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_38__   TYPE_1__ ;

/* Type definitions */
struct TYPE_38__ {int sign; } ;
typedef  TYPE_1__ mp_int ;

/* Variables and functions */
 scalar_t__ MP_EQ ; 
 scalar_t__ MP_LT ; 
 scalar_t__ MP_NEG ; 
 int MP_OKAY ; 
 int MP_VAL ; 
 int mp_abs (TYPE_1__ const*,TYPE_1__*) ; 
 int mp_add (TYPE_1__*,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  mp_clear_multi (TYPE_1__*,TYPE_1__*,TYPE_1__*,TYPE_1__*,TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ mp_cmp (TYPE_1__*,TYPE_1__*) ; 
 scalar_t__ mp_cmp_d (TYPE_1__*,int) ; 
 int mp_copy (TYPE_1__*,TYPE_1__*) ; 
 int mp_div_2 (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  mp_exch (TYPE_1__*,TYPE_1__*) ; 
 int mp_init_multi (TYPE_1__*,TYPE_1__*,TYPE_1__*,TYPE_1__*,TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int mp_iseven (TYPE_1__*) ; 
 int mp_isodd (TYPE_1__*) ; 
 scalar_t__ mp_iszero (TYPE_1__*) ; 
 int /*<<< orphan*/  mp_set (TYPE_1__*,int) ; 
 int mp_sub (TYPE_1__*,TYPE_1__*,TYPE_1__*) ; 

__attribute__((used)) static int
fast_mp_invmod (const mp_int * a, mp_int * b, mp_int * c)
{
  mp_int  x, y, u, v, B, D;
  int     res, neg;

  /* 2. [modified] b must be odd   */
  if (mp_iseven (b) == 1) {
    return MP_VAL;
  }

  /* init all our temps */
  if ((res = mp_init_multi(&x, &y, &u, &v, &B, &D, NULL)) != MP_OKAY) {
     return res;
  }

  /* x == modulus, y == value to invert */
  if ((res = mp_copy (b, &x)) != MP_OKAY) {
    goto __ERR;
  }

  /* we need y = |a| */
  if ((res = mp_abs (a, &y)) != MP_OKAY) {
    goto __ERR;
  }

  /* 3. u=x, v=y, A=1, B=0, C=0,D=1 */
  if ((res = mp_copy (&x, &u)) != MP_OKAY) {
    goto __ERR;
  }
  if ((res = mp_copy (&y, &v)) != MP_OKAY) {
    goto __ERR;
  }
  mp_set (&D, 1);

top:
  /* 4.  while u is even do */
  while (mp_iseven (&u) == 1) {
    /* 4.1 u = u/2 */
    if ((res = mp_div_2 (&u, &u)) != MP_OKAY) {
      goto __ERR;
    }
    /* 4.2 if B is odd then */
    if (mp_isodd (&B) == 1) {
      if ((res = mp_sub (&B, &x, &B)) != MP_OKAY) {
        goto __ERR;
      }
    }
    /* B = B/2 */
    if ((res = mp_div_2 (&B, &B)) != MP_OKAY) {
      goto __ERR;
    }
  }

  /* 5.  while v is even do */
  while (mp_iseven (&v) == 1) {
    /* 5.1 v = v/2 */
    if ((res = mp_div_2 (&v, &v)) != MP_OKAY) {
      goto __ERR;
    }
    /* 5.2 if D is odd then */
    if (mp_isodd (&D) == 1) {
      /* D = (D-x)/2 */
      if ((res = mp_sub (&D, &x, &D)) != MP_OKAY) {
        goto __ERR;
      }
    }
    /* D = D/2 */
    if ((res = mp_div_2 (&D, &D)) != MP_OKAY) {
      goto __ERR;
    }
  }

  /* 6.  if u >= v then */
  if (mp_cmp (&u, &v) != MP_LT) {
    /* u = u - v, B = B - D */
    if ((res = mp_sub (&u, &v, &u)) != MP_OKAY) {
      goto __ERR;
    }

    if ((res = mp_sub (&B, &D, &B)) != MP_OKAY) {
      goto __ERR;
    }
  } else {
    /* v - v - u, D = D - B */
    if ((res = mp_sub (&v, &u, &v)) != MP_OKAY) {
      goto __ERR;
    }

    if ((res = mp_sub (&D, &B, &D)) != MP_OKAY) {
      goto __ERR;
    }
  }

  /* if not zero goto step 4 */
  if (mp_iszero (&u) == 0) {
    goto top;
  }

  /* now a = C, b = D, gcd == g*v */

  /* if v != 1 then there is no inverse */
  if (mp_cmp_d (&v, 1) != MP_EQ) {
    res = MP_VAL;
    goto __ERR;
  }

  /* b is now the inverse */
  neg = a->sign;
  while (D.sign == MP_NEG) {
    if ((res = mp_add (&D, b, &D)) != MP_OKAY) {
      goto __ERR;
    }
  }
  mp_exch (&D, c);
  c->sign = neg;
  res = MP_OKAY;

__ERR:mp_clear_multi (&x, &y, &u, &v, &B, &D, NULL);
  return res;
}