#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct bpf_verifier_env {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  value; } ;
struct bpf_reg_state {int /*<<< orphan*/  off; int /*<<< orphan*/  smin_value; TYPE_1__ var_off; } ;
typedef  int /*<<< orphan*/  s64 ;
typedef  enum bpf_reg_type { ____Placeholder_bpf_reg_type } bpf_reg_type ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_MAX_VAR_OFF ; 
 int /*<<< orphan*/  S64_MIN ; 
 int /*<<< orphan*/ * reg_type_str ; 
 int tnum_is_const (TYPE_1__) ; 
 int /*<<< orphan*/  verbose (struct bpf_verifier_env*,char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static bool check_reg_sane_offset(struct bpf_verifier_env *env,
				  const struct bpf_reg_state *reg,
				  enum bpf_reg_type type)
{
	bool known = tnum_is_const(reg->var_off);
	s64 val = reg->var_off.value;
	s64 smin = reg->smin_value;

	if (known && (val >= BPF_MAX_VAR_OFF || val <= -BPF_MAX_VAR_OFF)) {
		verbose(env, "math between %s pointer and %lld is not allowed\n",
			reg_type_str[type], val);
		return false;
	}

	if (reg->off >= BPF_MAX_VAR_OFF || reg->off <= -BPF_MAX_VAR_OFF) {
		verbose(env, "%s pointer offset %d is not allowed\n",
			reg_type_str[type], reg->off);
		return false;
	}

	if (smin == S64_MIN) {
		verbose(env, "math between %s pointer and register with unbounded min value is not allowed\n",
			reg_type_str[type]);
		return false;
	}

	if (smin >= BPF_MAX_VAR_OFF || smin <= -BPF_MAX_VAR_OFF) {
		verbose(env, "value %lld makes %s pointer be out of bounds\n",
			smin, reg_type_str[type]);
		return false;
	}

	return true;
}