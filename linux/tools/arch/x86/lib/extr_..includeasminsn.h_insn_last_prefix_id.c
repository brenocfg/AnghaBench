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
struct TYPE_2__ {scalar_t__* bytes; } ;
struct insn {TYPE_1__ prefixes; } ;

/* Variables and functions */
 int inat_get_last_prefix_id (scalar_t__) ; 
 scalar_t__ insn_is_avx (struct insn*) ; 
 int insn_vex_p_bits (struct insn*) ; 

__attribute__((used)) static inline int insn_last_prefix_id(struct insn *insn)
{
	if (insn_is_avx(insn))
		return insn_vex_p_bits(insn);	/* VEX_p is a SIMD prefix id */

	if (insn->prefixes.bytes[3])
		return inat_get_last_prefix_id(insn->prefixes.bytes[3]);

	return 0;
}