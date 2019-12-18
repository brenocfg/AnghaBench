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
struct dim {scalar_t__ profile_ix; int /*<<< orphan*/  tune_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIM_GOING_LEFT ; 
 int /*<<< orphan*/  DIM_GOING_RIGHT ; 
 int /*<<< orphan*/  net_dim_step (struct dim*) ; 

__attribute__((used)) static void net_dim_exit_parking(struct dim *dim)
{
	dim->tune_state = dim->profile_ix ? DIM_GOING_LEFT : DIM_GOING_RIGHT;
	net_dim_step(dim);
}