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
typedef  int /*<<< orphan*/  mp_int ;

/* Variables and functions */
 scalar_t__ MP_EQ ; 
 int MP_NO ; 
 int MP_OKAY ; 
 int MP_VAL ; 
 int MP_YES ; 
 int PRIME_SIZE ; 
 int /*<<< orphan*/ * __prime_tab ; 
 int /*<<< orphan*/  mp_clear (int /*<<< orphan*/ *) ; 
 scalar_t__ mp_cmp_d (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int mp_init (int /*<<< orphan*/ *) ; 
 int mp_prime_is_divisible (int /*<<< orphan*/ *,int*) ; 
 int mp_prime_miller_rabin (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  mp_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mp_prime_is_prime (mp_int * a, int t, int *result)
{
  mp_int  b;
  int     ix, err, res;

  /* default to no */
  *result = MP_NO;

  /* valid value of t? */
  if (t <= 0 || t > PRIME_SIZE) {
    return MP_VAL;
  }

  /* is the input equal to one of the primes in the table? */
  for (ix = 0; ix < PRIME_SIZE; ix++) {
      if (mp_cmp_d(a, __prime_tab[ix]) == MP_EQ) {
         *result = 1;
         return MP_OKAY;
      }
  }

  /* first perform trial division */
  if ((err = mp_prime_is_divisible (a, &res)) != MP_OKAY) {
    return err;
  }

  /* return if it was trivially divisible */
  if (res == MP_YES) {
    return MP_OKAY;
  }

  /* now perform the miller-rabin rounds */
  if ((err = mp_init (&b)) != MP_OKAY) {
    return err;
  }

  for (ix = 0; ix < t; ix++) {
    /* set the prime */
    mp_set (&b, __prime_tab[ix]);

    if ((err = mp_prime_miller_rabin (a, &b, &res)) != MP_OKAY) {
      goto __B;
    }

    if (res == MP_NO) {
      goto __B;
    }
  }

  /* passed the test */
  *result = MP_YES;
__B:mp_clear (&b);
  return err;
}