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
typedef  int u64 ;
typedef  int u32 ;
struct cobalt_vars {int rec_inv_sqrt; scalar_t__ count; } ;

/* Variables and functions */

__attribute__((used)) static void cobalt_newton_step(struct cobalt_vars *vars)
{
	u32 invsqrt, invsqrt2;
	u64 val;

	invsqrt = vars->rec_inv_sqrt;
	invsqrt2 = ((u64)invsqrt * invsqrt) >> 32;
	val = (3LL << 32) - ((u64)vars->count * invsqrt2);

	val >>= 2; /* avoid overflow in following multiply */
	val = (val * invsqrt) >> (32 - 2 + 1);

	vars->rec_inv_sqrt = val;
}