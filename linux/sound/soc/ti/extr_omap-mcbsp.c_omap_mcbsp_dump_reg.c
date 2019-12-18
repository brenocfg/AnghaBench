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
struct omap_mcbsp {int /*<<< orphan*/  dev; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRR1 ; 
 int /*<<< orphan*/  DRR2 ; 
 int /*<<< orphan*/  DXR1 ; 
 int /*<<< orphan*/  DXR2 ; 
 int /*<<< orphan*/  MCBSP_READ (struct omap_mcbsp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCR0 ; 
 int /*<<< orphan*/  RCR1 ; 
 int /*<<< orphan*/  RCR2 ; 
 int /*<<< orphan*/  SPCR1 ; 
 int /*<<< orphan*/  SPCR2 ; 
 int /*<<< orphan*/  SRGR1 ; 
 int /*<<< orphan*/  SRGR2 ; 
 int /*<<< orphan*/  XCR1 ; 
 int /*<<< orphan*/  XCR2 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void omap_mcbsp_dump_reg(struct omap_mcbsp *mcbsp)
{
	dev_dbg(mcbsp->dev, "**** McBSP%d regs ****\n", mcbsp->id);
	dev_dbg(mcbsp->dev, "DRR2:  0x%04x\n", MCBSP_READ(mcbsp, DRR2));
	dev_dbg(mcbsp->dev, "DRR1:  0x%04x\n", MCBSP_READ(mcbsp, DRR1));
	dev_dbg(mcbsp->dev, "DXR2:  0x%04x\n", MCBSP_READ(mcbsp, DXR2));
	dev_dbg(mcbsp->dev, "DXR1:  0x%04x\n", MCBSP_READ(mcbsp, DXR1));
	dev_dbg(mcbsp->dev, "SPCR2: 0x%04x\n", MCBSP_READ(mcbsp, SPCR2));
	dev_dbg(mcbsp->dev, "SPCR1: 0x%04x\n", MCBSP_READ(mcbsp, SPCR1));
	dev_dbg(mcbsp->dev, "RCR2:  0x%04x\n", MCBSP_READ(mcbsp, RCR2));
	dev_dbg(mcbsp->dev, "RCR1:  0x%04x\n", MCBSP_READ(mcbsp, RCR1));
	dev_dbg(mcbsp->dev, "XCR2:  0x%04x\n", MCBSP_READ(mcbsp, XCR2));
	dev_dbg(mcbsp->dev, "XCR1:  0x%04x\n", MCBSP_READ(mcbsp, XCR1));
	dev_dbg(mcbsp->dev, "SRGR2: 0x%04x\n", MCBSP_READ(mcbsp, SRGR2));
	dev_dbg(mcbsp->dev, "SRGR1: 0x%04x\n", MCBSP_READ(mcbsp, SRGR1));
	dev_dbg(mcbsp->dev, "PCR0:  0x%04x\n", MCBSP_READ(mcbsp, PCR0));
	dev_dbg(mcbsp->dev, "***********************\n");
}