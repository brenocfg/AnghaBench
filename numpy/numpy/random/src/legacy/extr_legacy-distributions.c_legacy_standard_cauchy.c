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
 double legacy_gauss (int /*<<< orphan*/ *) ; 

double legacy_standard_cauchy(aug_bitgen_t *aug_state) {
  return legacy_gauss(aug_state) / legacy_gauss(aug_state);
}