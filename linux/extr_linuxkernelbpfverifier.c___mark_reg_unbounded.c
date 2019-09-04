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
struct bpf_reg_state {int /*<<< orphan*/  umax_value; scalar_t__ umin_value; int /*<<< orphan*/  smax_value; int /*<<< orphan*/  smin_value; } ;

/* Variables and functions */
 int /*<<< orphan*/  S64_MAX ; 
 int /*<<< orphan*/  S64_MIN ; 
 int /*<<< orphan*/  U64_MAX ; 

__attribute__((used)) static void __mark_reg_unbounded(struct bpf_reg_state *reg)
{
	reg->smin_value = S64_MIN;
	reg->smax_value = S64_MAX;
	reg->umin_value = 0;
	reg->umax_value = U64_MAX;
}