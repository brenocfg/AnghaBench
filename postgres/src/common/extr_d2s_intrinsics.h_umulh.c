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
typedef  int /*<<< orphan*/  uint64 ;

/* Variables and functions */
 int /*<<< orphan*/  umul128 (int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline uint64
umulh(const uint64 a, const uint64 b)
{
	/*
	 * Reuse the umul128 implementation. Optimizers will likely eliminate the
	 * instructions used to compute the low part of the product.
	 */
	uint64		hi;

	umul128(a, b, &hi);
	return hi;
}