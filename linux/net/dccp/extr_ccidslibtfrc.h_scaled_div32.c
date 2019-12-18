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
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;

/* Variables and functions */
 int /*<<< orphan*/  DCCP_CRIT (char*,unsigned long long,unsigned long long) ; 
 scalar_t__ UINT_MAX ; 
 scalar_t__ scaled_div (scalar_t__,scalar_t__) ; 

__attribute__((used)) static inline u32 scaled_div32(u64 a, u64 b)
{
	u64 result = scaled_div(a, b);

	if (result > UINT_MAX) {
		DCCP_CRIT("Overflow: %llu/%llu > UINT_MAX",
			  (unsigned long long)a, (unsigned long long)b);
		return UINT_MAX;
	}
	return result;
}