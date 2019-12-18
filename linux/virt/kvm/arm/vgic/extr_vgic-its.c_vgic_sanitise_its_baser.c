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
 int /*<<< orphan*/  GITS_BASER_INNER_CACHEABILITY_MASK ; 
 int /*<<< orphan*/  GITS_BASER_INNER_CACHEABILITY_SHIFT ; 
 int /*<<< orphan*/  GITS_BASER_OUTER_CACHEABILITY_MASK ; 
 int /*<<< orphan*/  GITS_BASER_OUTER_CACHEABILITY_SHIFT ; 
 int GITS_BASER_PAGE_SIZE_64K ; 
 int GITS_BASER_PAGE_SIZE_MASK ; 
 int /*<<< orphan*/  GITS_BASER_SHAREABILITY_MASK ; 
 int /*<<< orphan*/  GITS_BASER_SHAREABILITY_SHIFT ; 
 int vgic_sanitise_field (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vgic_sanitise_inner_cacheability ; 
 int /*<<< orphan*/  vgic_sanitise_outer_cacheability ; 
 int /*<<< orphan*/  vgic_sanitise_shareability ; 

__attribute__((used)) static u64 vgic_sanitise_its_baser(u64 reg)
{
	reg = vgic_sanitise_field(reg, GITS_BASER_SHAREABILITY_MASK,
				  GITS_BASER_SHAREABILITY_SHIFT,
				  vgic_sanitise_shareability);
	reg = vgic_sanitise_field(reg, GITS_BASER_INNER_CACHEABILITY_MASK,
				  GITS_BASER_INNER_CACHEABILITY_SHIFT,
				  vgic_sanitise_inner_cacheability);
	reg = vgic_sanitise_field(reg, GITS_BASER_OUTER_CACHEABILITY_MASK,
				  GITS_BASER_OUTER_CACHEABILITY_SHIFT,
				  vgic_sanitise_outer_cacheability);

	/* We support only one (ITS) page size: 64K */
	reg = (reg & ~GITS_BASER_PAGE_SIZE_MASK) | GITS_BASER_PAGE_SIZE_64K;

	return reg;
}