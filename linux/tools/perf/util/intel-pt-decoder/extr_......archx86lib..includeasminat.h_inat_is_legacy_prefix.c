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
typedef  int /*<<< orphan*/  insn_attr_t ;

/* Variables and functions */
 int /*<<< orphan*/  INAT_LGCPFX_MAX ; 
 int /*<<< orphan*/  INAT_PFX_MASK ; 

__attribute__((used)) static inline int inat_is_legacy_prefix(insn_attr_t attr)
{
	attr &= INAT_PFX_MASK;
	return attr && attr <= INAT_LGCPFX_MAX;
}