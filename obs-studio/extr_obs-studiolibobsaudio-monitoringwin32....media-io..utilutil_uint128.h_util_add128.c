#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int low; int high; void** i32; } ;
typedef  TYPE_1__ util_uint128_t ;
typedef  int uint64_t ;
typedef  void* uint32_t ;

/* Variables and functions */

__attribute__((used)) static inline util_uint128_t util_add128(util_uint128_t a, util_uint128_t b)
{
	util_uint128_t out;
	uint64_t val;

	val = (a.low & 0xFFFFFFFFULL) + (b.low & 0xFFFFFFFFULL);
	out.i32[0] = (uint32_t)(val & 0xFFFFFFFFULL);
	val >>= 32;

	val += (a.low >> 32) + (b.low >> 32);
	out.i32[1] = (uint32_t)val;
	val >>= 32;

	val += (a.high & 0xFFFFFFFFULL) + (b.high & 0xFFFFFFFFULL);
	out.i32[2] = (uint32_t)(val & 0xFFFFFFFFULL);
	val >>= 32;

	val += (a.high >> 32) + (b.high >> 32);
	out.i32[3] = (uint32_t)val;

	return out;
}