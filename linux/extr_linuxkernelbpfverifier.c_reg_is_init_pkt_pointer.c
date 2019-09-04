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
struct bpf_reg_state {int type; scalar_t__ id; scalar_t__ off; int /*<<< orphan*/  var_off; } ;
typedef  enum bpf_reg_type { ____Placeholder_bpf_reg_type } bpf_reg_type ;

/* Variables and functions */
 scalar_t__ tnum_equals_const (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool reg_is_init_pkt_pointer(const struct bpf_reg_state *reg,
				    enum bpf_reg_type which)
{
	/* The register can already have a range from prior markings.
	 * This is fine as long as it hasn't been advanced from its
	 * origin.
	 */
	return reg->type == which &&
	       reg->id == 0 &&
	       reg->off == 0 &&
	       tnum_equals_const(reg->var_off, 0);
}