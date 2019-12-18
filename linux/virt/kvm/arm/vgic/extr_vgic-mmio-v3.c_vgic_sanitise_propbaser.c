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
typedef  int /*<<< orphan*/  u64 ;

/* Variables and functions */
 int /*<<< orphan*/  GICR_PROPBASER_INNER_CACHEABILITY_MASK ; 
 int /*<<< orphan*/  GICR_PROPBASER_INNER_CACHEABILITY_SHIFT ; 
 int /*<<< orphan*/  GICR_PROPBASER_OUTER_CACHEABILITY_MASK ; 
 int /*<<< orphan*/  GICR_PROPBASER_OUTER_CACHEABILITY_SHIFT ; 
 int /*<<< orphan*/  GICR_PROPBASER_SHAREABILITY_MASK ; 
 int /*<<< orphan*/  GICR_PROPBASER_SHAREABILITY_SHIFT ; 
 int /*<<< orphan*/  PROPBASER_RES0_MASK ; 
 int /*<<< orphan*/  vgic_sanitise_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vgic_sanitise_inner_cacheability ; 
 int /*<<< orphan*/  vgic_sanitise_outer_cacheability ; 
 int /*<<< orphan*/  vgic_sanitise_shareability ; 

__attribute__((used)) static u64 vgic_sanitise_propbaser(u64 reg)
{
	reg = vgic_sanitise_field(reg, GICR_PROPBASER_SHAREABILITY_MASK,
				  GICR_PROPBASER_SHAREABILITY_SHIFT,
				  vgic_sanitise_shareability);
	reg = vgic_sanitise_field(reg, GICR_PROPBASER_INNER_CACHEABILITY_MASK,
				  GICR_PROPBASER_INNER_CACHEABILITY_SHIFT,
				  vgic_sanitise_inner_cacheability);
	reg = vgic_sanitise_field(reg, GICR_PROPBASER_OUTER_CACHEABILITY_MASK,
				  GICR_PROPBASER_OUTER_CACHEABILITY_SHIFT,
				  vgic_sanitise_outer_cacheability);

	reg &= ~PROPBASER_RES0_MASK;
	return reg;
}