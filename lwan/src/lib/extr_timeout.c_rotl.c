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
typedef  int wheel_t ;
typedef  int const uint32_t ;

/* Variables and functions */
 int const WHEEL_T_BITS ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static inline wheel_t rotl(const wheel_t v, uint32_t n)
{
    assert(n < WHEEL_T_BITS);
    return (v << n) | (v >> (-n & (WHEEL_T_BITS - 1)));
}