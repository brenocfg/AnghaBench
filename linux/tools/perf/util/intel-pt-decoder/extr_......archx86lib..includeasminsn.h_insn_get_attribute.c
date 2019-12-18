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
struct insn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  insn_get_modrm (struct insn*) ; 

__attribute__((used)) static inline void insn_get_attribute(struct insn *insn)
{
	insn_get_modrm(insn);
}