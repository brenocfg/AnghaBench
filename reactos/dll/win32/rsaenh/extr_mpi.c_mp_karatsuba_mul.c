#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int used; int /*<<< orphan*/ * dp; } ;
typedef  TYPE_1__ mp_int ;
typedef  int /*<<< orphan*/  mp_digit ;

/* Variables and functions */
 int MIN (int,int) ; 
 int MP_MEM ; 
 int MP_OKAY ; 
 int mp_add (TYPE_1__*,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  mp_clamp (TYPE_1__*) ; 
 int /*<<< orphan*/  mp_clear (TYPE_1__*) ; 
 int mp_init_size (TYPE_1__*,int) ; 
 int mp_lshd (TYPE_1__*,int) ; 
 int mp_mul (TYPE_1__*,TYPE_1__*,TYPE_1__*) ; 
 int mp_sub (TYPE_1__*,TYPE_1__*,TYPE_1__*) ; 

int mp_karatsuba_mul (const mp_int * a, const mp_int * b, mp_int * c)
{
  mp_int  x0, x1, y0, y1, t1, x0y0, x1y1;
  int     B, err;

  /* default the return code to an error */
  err = MP_MEM;

  /* min # of digits */
  B = MIN (a->used, b->used);

  /* now divide in two */
  B = B >> 1;

  /* init copy all the temps */
  if (mp_init_size (&x0, B) != MP_OKAY)
    goto ERR;
  if (mp_init_size (&x1, a->used - B) != MP_OKAY)
    goto X0;
  if (mp_init_size (&y0, B) != MP_OKAY)
    goto X1;
  if (mp_init_size (&y1, b->used - B) != MP_OKAY)
    goto Y0;

  /* init temps */
  if (mp_init_size (&t1, B * 2) != MP_OKAY)
    goto Y1;
  if (mp_init_size (&x0y0, B * 2) != MP_OKAY)
    goto T1;
  if (mp_init_size (&x1y1, B * 2) != MP_OKAY)
    goto X0Y0;

  /* now shift the digits */
  x0.used = y0.used = B;
  x1.used = a->used - B;
  y1.used = b->used - B;

  {
    register int x;
    register mp_digit *tmpa, *tmpb, *tmpx, *tmpy;

    /* we copy the digits directly instead of using higher level functions
     * since we also need to shift the digits
     */
    tmpa = a->dp;
    tmpb = b->dp;

    tmpx = x0.dp;
    tmpy = y0.dp;
    for (x = 0; x < B; x++) {
      *tmpx++ = *tmpa++;
      *tmpy++ = *tmpb++;
    }

    tmpx = x1.dp;
    for (x = B; x < a->used; x++) {
      *tmpx++ = *tmpa++;
    }

    tmpy = y1.dp;
    for (x = B; x < b->used; x++) {
      *tmpy++ = *tmpb++;
    }
  }

  /* only need to clamp the lower words since by definition the 
   * upper words x1/y1 must have a known number of digits
   */
  mp_clamp (&x0);
  mp_clamp (&y0);

  /* now calc the products x0y0 and x1y1 */
  /* after this x0 is no longer required, free temp [x0==t2]! */
  if (mp_mul (&x0, &y0, &x0y0) != MP_OKAY)  
    goto X1Y1;          /* x0y0 = x0*y0 */
  if (mp_mul (&x1, &y1, &x1y1) != MP_OKAY)
    goto X1Y1;          /* x1y1 = x1*y1 */

  /* now calc x1-x0 and y1-y0 */
  if (mp_sub (&x1, &x0, &t1) != MP_OKAY)
    goto X1Y1;          /* t1 = x1 - x0 */
  if (mp_sub (&y1, &y0, &x0) != MP_OKAY)
    goto X1Y1;          /* t2 = y1 - y0 */
  if (mp_mul (&t1, &x0, &t1) != MP_OKAY)
    goto X1Y1;          /* t1 = (x1 - x0) * (y1 - y0) */

  /* add x0y0 */
  if (mp_add (&x0y0, &x1y1, &x0) != MP_OKAY)
    goto X1Y1;          /* t2 = x0y0 + x1y1 */
  if (mp_sub (&x0, &t1, &t1) != MP_OKAY)
    goto X1Y1;          /* t1 = x0y0 + x1y1 - (x1-x0)*(y1-y0) */

  /* shift by B */
  if (mp_lshd (&t1, B) != MP_OKAY)
    goto X1Y1;          /* t1 = (x0y0 + x1y1 - (x1-x0)*(y1-y0))<<B */
  if (mp_lshd (&x1y1, B * 2) != MP_OKAY)
    goto X1Y1;          /* x1y1 = x1y1 << 2*B */

  if (mp_add (&x0y0, &t1, &t1) != MP_OKAY)
    goto X1Y1;          /* t1 = x0y0 + t1 */
  if (mp_add (&t1, &x1y1, c) != MP_OKAY)
    goto X1Y1;          /* t1 = x0y0 + t1 + x1y1 */

  /* Algorithm succeeded set the return code to MP_OKAY */
  err = MP_OKAY;

X1Y1:mp_clear (&x1y1);
X0Y0:mp_clear (&x0y0);
T1:mp_clear (&t1);
Y1:mp_clear (&y1);
Y0:mp_clear (&y0);
X1:mp_clear (&x1);
X0:mp_clear (&x0);
ERR:
  return err;
}