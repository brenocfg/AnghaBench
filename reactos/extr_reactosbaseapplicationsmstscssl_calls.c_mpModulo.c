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
typedef  int /*<<< orphan*/  DIGIT_T ;

/* Variables and functions */
 int MAX_DIG_LEN ; 
 int /*<<< orphan*/  mpDivide (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  mpSetEqual (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  mpSetZero (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static int
mpModulo(DIGIT_T* r, DIGIT_T* u, unsigned int udigits,
         DIGIT_T* v, unsigned int vdigits)
{
  /* Calculates r = u mod v
     where r, v are multiprecision integers of length vdigits
     and u is a multiprecision integer of length udigits.
     r may overlap v.

     Note that r here is only vdigits long,
     whereas in mpDivide it is udigits long.

     Use remainder from mpDivide function. */
  /* Double-length temp variable for divide fn */
  DIGIT_T qq[MAX_DIG_LEN * 2];
  /* Use a double-length temp for r to allow overlap of r and v */
  DIGIT_T rr[MAX_DIG_LEN * 2];

  /* rr[2n] = u[2n] mod v[n] */
  mpDivide(qq, rr, u, udigits, v, vdigits);
  mpSetEqual(r, rr, vdigits);
  mpSetZero(rr, udigits);
  mpSetZero(qq, udigits);
  return 0;
}