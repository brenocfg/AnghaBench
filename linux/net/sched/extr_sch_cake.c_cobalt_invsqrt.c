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
struct cobalt_vars {size_t count; int /*<<< orphan*/  rec_inv_sqrt; } ;

/* Variables and functions */
 size_t REC_INV_SQRT_CACHE ; 
 int /*<<< orphan*/  cobalt_newton_step (struct cobalt_vars*) ; 
 int /*<<< orphan*/ * cobalt_rec_inv_sqrt_cache ; 

__attribute__((used)) static void cobalt_invsqrt(struct cobalt_vars *vars)
{
	if (vars->count < REC_INV_SQRT_CACHE)
		vars->rec_inv_sqrt = cobalt_rec_inv_sqrt_cache[vars->count];
	else
		cobalt_newton_step(vars);
}