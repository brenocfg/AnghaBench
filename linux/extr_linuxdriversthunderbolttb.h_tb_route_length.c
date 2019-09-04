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
typedef  int /*<<< orphan*/  u64 ;

/* Variables and functions */
 int TB_ROUTE_SHIFT ; 
 int fls64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int tb_route_length(u64 route)
{
	return (fls64(route) + TB_ROUTE_SHIFT - 1) / TB_ROUTE_SHIFT;
}