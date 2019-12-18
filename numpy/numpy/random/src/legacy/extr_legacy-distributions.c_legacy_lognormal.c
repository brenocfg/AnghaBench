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
typedef  int /*<<< orphan*/  aug_bitgen_t ;

/* Variables and functions */
 double exp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  legacy_normal (int /*<<< orphan*/ *,double,double) ; 

double legacy_lognormal(aug_bitgen_t *aug_state, double mean, double sigma) {
  return exp(legacy_normal(aug_state, mean, sigma));
}