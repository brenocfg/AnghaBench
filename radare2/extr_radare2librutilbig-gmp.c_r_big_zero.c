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
typedef  int /*<<< orphan*/  RNumBig ;

/* Variables and functions */
 int /*<<< orphan*/  mpz_init (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void r_big_zero(RNumBig *n) {
	mpz_init (*n);
}