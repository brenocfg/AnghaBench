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
struct bpf_reg_state {scalar_t__ type; int /*<<< orphan*/  var_off; } ;

/* Variables and functions */
 scalar_t__ SCALAR_VALUE ; 
 scalar_t__ tnum_equals_const (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool register_is_null(struct bpf_reg_state *reg)
{
	return reg->type == SCALAR_VALUE && tnum_equals_const(reg->var_off, 0);
}