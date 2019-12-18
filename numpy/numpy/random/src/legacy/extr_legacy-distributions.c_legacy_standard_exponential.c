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
 scalar_t__ legacy_double (int /*<<< orphan*/ *) ; 
 double log (scalar_t__) ; 

double legacy_standard_exponential(aug_bitgen_t *aug_state) {
  /* We use -log(1-U) since U is [0, 1) */
  return -log(1.0 - legacy_double(aug_state));
}