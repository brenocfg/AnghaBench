#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int used; } ;
typedef  TYPE_1__ mp_int ;

/* Variables and functions */
 int DIGIT_BIT ; 
 scalar_t__ MP_LT ; 
 int MP_OKAY ; 
 int mp_2expt (TYPE_1__*,int) ; 
 scalar_t__ mp_cmp_mag (TYPE_1__*,TYPE_1__ const*) ; 
 int mp_count_bits (TYPE_1__ const*) ; 
 int mp_mul_2 (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  mp_set (TYPE_1__*,int) ; 
 int s_mp_sub (TYPE_1__*,TYPE_1__ const*,TYPE_1__*) ; 

int mp_montgomery_calc_normalization (mp_int * a, const mp_int * b)
{
  int     x, bits, res;

  /* how many bits of last digit does b use */
  bits = mp_count_bits (b) % DIGIT_BIT;


  if (b->used > 1) {
     if ((res = mp_2expt (a, (b->used - 1) * DIGIT_BIT + bits - 1)) != MP_OKAY) {
        return res;
     }
  } else {
     mp_set(a, 1);
     bits = 1;
  }


  /* now compute C = A * B mod b */
  for (x = bits - 1; x < DIGIT_BIT; x++) {
    if ((res = mp_mul_2 (a, a)) != MP_OKAY) {
      return res;
    }
    if (mp_cmp_mag (a, b) != MP_LT) {
      if ((res = s_mp_sub (a, b, a)) != MP_OKAY) {
        return res;
      }
    }
  }

  return MP_OKAY;
}