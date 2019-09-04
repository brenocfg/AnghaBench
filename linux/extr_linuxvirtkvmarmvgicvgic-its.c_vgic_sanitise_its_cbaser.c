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
typedef  int u64 ;

/* Variables and functions */
 int GENMASK_ULL (int,int) ; 
 int /*<<< orphan*/  GITS_CBASER_INNER_CACHEABILITY_MASK ; 
 int /*<<< orphan*/  GITS_CBASER_INNER_CACHEABILITY_SHIFT ; 
 int /*<<< orphan*/  GITS_CBASER_OUTER_CACHEABILITY_MASK ; 
 int /*<<< orphan*/  GITS_CBASER_OUTER_CACHEABILITY_SHIFT ; 
 int /*<<< orphan*/  GITS_CBASER_SHAREABILITY_MASK ; 
 int /*<<< orphan*/  GITS_CBASER_SHAREABILITY_SHIFT ; 
 int vgic_sanitise_field (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vgic_sanitise_inner_cacheability ; 
 int /*<<< orphan*/  vgic_sanitise_outer_cacheability ; 
 int /*<<< orphan*/  vgic_sanitise_shareability ; 

__attribute__((used)) static u64 vgic_sanitise_its_cbaser(u64 reg)
{
	reg = vgic_sanitise_field(reg, GITS_CBASER_SHAREABILITY_MASK,
				  GITS_CBASER_SHAREABILITY_SHIFT,
				  vgic_sanitise_shareability);
	reg = vgic_sanitise_field(reg, GITS_CBASER_INNER_CACHEABILITY_MASK,
				  GITS_CBASER_INNER_CACHEABILITY_SHIFT,
				  vgic_sanitise_inner_cacheability);
	reg = vgic_sanitise_field(reg, GITS_CBASER_OUTER_CACHEABILITY_MASK,
				  GITS_CBASER_OUTER_CACHEABILITY_SHIFT,
				  vgic_sanitise_outer_cacheability);

	/*
	 * Sanitise the physical address to be 64k aligned.
	 * Also limit the physical addresses to 48 bits.
	 */
	reg &= ~(GENMASK_ULL(51, 48) | GENMASK_ULL(15, 12));

	return reg;
}