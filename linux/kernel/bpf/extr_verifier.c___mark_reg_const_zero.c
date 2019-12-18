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
struct bpf_reg_state {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCALAR_VALUE ; 
 int /*<<< orphan*/  __mark_reg_known (struct bpf_reg_state*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __mark_reg_const_zero(struct bpf_reg_state *reg)
{
	__mark_reg_known(reg, 0);
	reg->type = SCALAR_VALUE;
}