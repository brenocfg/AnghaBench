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
struct pxafb_mach_info {int lccr0; int lccr3; TYPE_1__* modes; scalar_t__ lcd_conn; } ;
struct device {int dummy; } ;
struct TYPE_2__ {scalar_t__ lower_margin; scalar_t__ upper_margin; } ;

/* Variables and functions */
 int LCCR0_Act ; 
 int LCCR0_CMS ; 
 int LCCR0_DPD ; 
 int LCCR0_Dual ; 
 int LCCR0_INVALID_CONFIG_MASK ; 
 int LCCR0_Mono ; 
 int LCCR0_PAS ; 
 int LCCR0_Pas ; 
 int LCCR0_SDS ; 
 int LCCR0_Sngl ; 
 int LCCR3_INVALID_CONFIG_MASK ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,...) ; 

__attribute__((used)) static void pxafb_check_options(struct device *dev, struct pxafb_mach_info *inf)
{
	if (inf->lcd_conn)
		return;

	if (inf->lccr0 & LCCR0_INVALID_CONFIG_MASK)
		dev_warn(dev, "machine LCCR0 setting contains "
				"illegal bits: %08x\n",
			inf->lccr0 & LCCR0_INVALID_CONFIG_MASK);
	if (inf->lccr3 & LCCR3_INVALID_CONFIG_MASK)
		dev_warn(dev, "machine LCCR3 setting contains "
				"illegal bits: %08x\n",
			inf->lccr3 & LCCR3_INVALID_CONFIG_MASK);
	if (inf->lccr0 & LCCR0_DPD &&
	    ((inf->lccr0 & LCCR0_PAS) != LCCR0_Pas ||
	     (inf->lccr0 & LCCR0_SDS) != LCCR0_Sngl ||
	     (inf->lccr0 & LCCR0_CMS) != LCCR0_Mono))
		dev_warn(dev, "Double Pixel Data (DPD) mode is "
				"only valid in passive mono"
				" single panel mode\n");
	if ((inf->lccr0 & LCCR0_PAS) == LCCR0_Act &&
	    (inf->lccr0 & LCCR0_SDS) == LCCR0_Dual)
		dev_warn(dev, "Dual panel only valid in passive mode\n");
	if ((inf->lccr0 & LCCR0_PAS) == LCCR0_Pas &&
	     (inf->modes->upper_margin || inf->modes->lower_margin))
		dev_warn(dev, "Upper and lower margins must be 0 in "
				"passive mode\n");
}