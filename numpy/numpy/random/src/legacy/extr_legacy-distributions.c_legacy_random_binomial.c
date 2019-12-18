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
typedef  scalar_t__ int64_t ;
typedef  int /*<<< orphan*/  bitgen_t ;
typedef  int /*<<< orphan*/  binomial_t ;
typedef  int /*<<< orphan*/  RAND_INT_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  legacy_random_binomial_original (int /*<<< orphan*/ *,double,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int64_t legacy_random_binomial(bitgen_t *bitgen_state, double p,
                               int64_t n, binomial_t *binomial) {
  return (int64_t) legacy_random_binomial_original(bitgen_state, p,
                                                   (RAND_INT_TYPE) n,
                                                   binomial);
}