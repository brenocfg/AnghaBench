#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ sign; } ;
typedef  TYPE_1__ mp_int ;

/* Variables and functions */
 scalar_t__ MP_NEG ; 
 int MP_VAL ; 
 int fast_mp_invmod (TYPE_1__ const*,TYPE_1__*,TYPE_1__*) ; 
 int mp_invmod_slow (TYPE_1__ const*,TYPE_1__*,TYPE_1__*) ; 
 int mp_isodd (TYPE_1__*) ; 
 int mp_iszero (TYPE_1__*) ; 

int mp_invmod (const mp_int * a, mp_int * b, mp_int * c)
{
  /* b cannot be negative */
  if (b->sign == MP_NEG || mp_iszero(b) == 1) {
    return MP_VAL;
  }

  /* if the modulus is odd we can use a faster routine instead */
  if (mp_isodd (b) == 1) {
    return fast_mp_invmod (a, b, c);
  }
  
  return mp_invmod_slow(a, b, c);
}