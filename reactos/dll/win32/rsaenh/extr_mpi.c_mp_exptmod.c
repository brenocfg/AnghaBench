#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_1__ ;

/* Type definitions */
struct TYPE_24__ {scalar_t__ sign; } ;
typedef  TYPE_1__ mp_int ;

/* Variables and functions */
 scalar_t__ MP_NEG ; 
 int MP_OKAY ; 
 int MP_VAL ; 
 int mp_abs (TYPE_1__ const*,TYPE_1__*) ; 
 int /*<<< orphan*/  mp_clear (TYPE_1__*) ; 
 int /*<<< orphan*/  mp_clear_multi (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int mp_exptmod_fast (TYPE_1__ const*,TYPE_1__ const*,TYPE_1__*,TYPE_1__*,int) ; 
 int mp_init (TYPE_1__*) ; 
 int mp_invmod (TYPE_1__ const*,TYPE_1__*,TYPE_1__*) ; 
 int mp_isodd (TYPE_1__*) ; 
 int s_mp_exptmod (TYPE_1__ const*,TYPE_1__ const*,TYPE_1__*,TYPE_1__*) ; 

int mp_exptmod (const mp_int * G, const mp_int * X, mp_int * P, mp_int * Y)
{
  int dr;

  /* modulus P must be positive */
  if (P->sign == MP_NEG) {
     return MP_VAL;
  }

  /* if exponent X is negative we have to recurse */
  if (X->sign == MP_NEG) {
     mp_int tmpG, tmpX;
     int err;

     /* first compute 1/G mod P */
     if ((err = mp_init(&tmpG)) != MP_OKAY) {
        return err;
     }
     if ((err = mp_invmod(G, P, &tmpG)) != MP_OKAY) {
        mp_clear(&tmpG);
        return err;
     }

     /* now get |X| */
     if ((err = mp_init(&tmpX)) != MP_OKAY) {
        mp_clear(&tmpG);
        return err;
     }
     if ((err = mp_abs(X, &tmpX)) != MP_OKAY) {
        mp_clear_multi(&tmpG, &tmpX, NULL);
        return err;
     }

     /* and now compute (1/G)**|X| instead of G**X [X < 0] */
     err = mp_exptmod(&tmpG, &tmpX, P, Y);
     mp_clear_multi(&tmpG, &tmpX, NULL);
     return err;
  }

  dr = 0;

  /* if the modulus is odd use the fast method */
  if (mp_isodd (P) == 1) {
    return mp_exptmod_fast (G, X, P, Y, dr);
  } else {
    /* otherwise use the generic Barrett reduction technique */
    return s_mp_exptmod (G, X, P, Y);
  }
}