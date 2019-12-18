#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  high; scalar_t__ low; } ;
typedef  TYPE_1__ util_uint128_t ;
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */

__attribute__((used)) static inline util_uint128_t util_lshift64_internal_64(uint64_t a)
{
	util_uint128_t val;
	val.low = 0;
	val.high = a;
	return val;
}