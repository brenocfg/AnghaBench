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
typedef  int /*<<< orphan*/  npy_intp ;
typedef  int /*<<< orphan*/  bitgen_t ;
typedef  int /*<<< orphan*/  binomial_t ;
typedef  int /*<<< orphan*/  RAND_INT_TYPE ;

/* Variables and functions */
 void random_multinomial (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,double*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void legacy_random_multinomial(bitgen_t *bitgen_state, RAND_INT_TYPE n,
                               RAND_INT_TYPE *mnix, double *pix, npy_intp d,
                               binomial_t *binomial) {
  return random_multinomial(bitgen_state, n, mnix, pix, d, binomial);
}