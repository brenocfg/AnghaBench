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
 int type_is_pkt_pointer (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool reg_is_pkt_pointer(const struct bpf_reg_state *reg)
{
	return type_is_pkt_pointer(reg->type);
}