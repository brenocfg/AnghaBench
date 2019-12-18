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
typedef  size_t uint32 ;
typedef  int /*<<< orphan*/  int32 ;

/* Variables and functions */
 int /*<<< orphan*/ * FLOAT_POW5_SPLIT ; 
 size_t mulShift (size_t const,int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 

__attribute__((used)) static inline uint32
mulPow5divPow2(const uint32 m, const uint32 i, const int32 j)
{
	return mulShift(m, FLOAT_POW5_SPLIT[i], j);
}