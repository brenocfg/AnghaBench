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
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  bitgen_t ;

/* Variables and functions */
 int /*<<< orphan*/  random_zipf (int /*<<< orphan*/ *,double) ; 

int64_t legacy_random_zipf(bitgen_t *bitgen_state, double a) {
  return (int64_t)random_zipf(bitgen_state, a);
}