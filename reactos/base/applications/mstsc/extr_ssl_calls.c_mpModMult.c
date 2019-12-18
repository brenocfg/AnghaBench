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
 int /*<<< orphan*/  mpModulo (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  mpMultiply (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  mpSetZero (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static int
mpModMult(DIGIT_T* a, DIGIT_T* x, DIGIT_T* y,
          DIGIT_T* m, unsigned int ndigits)
{ /* Computes a = (x * y) mod m */
  /* Double-length temp variable */
  DIGIT_T p[MAX_DIG_LEN * 2];

  /* Calc p[2n] = x * y */
  mpMultiply(p, x, y, ndigits);
  /* Then modulo */
  mpModulo(a, p, ndigits * 2, m, ndigits);
  mpSetZero(p, ndigits * 2);
  return 0;
}