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
struct seq_file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RFBI_CMD ; 
 int /*<<< orphan*/  RFBI_CONFIG (int) ; 
 int /*<<< orphan*/  RFBI_CONTROL ; 
 int /*<<< orphan*/  RFBI_CYCLE_TIME (int) ; 
 int /*<<< orphan*/  RFBI_DATA ; 
 int /*<<< orphan*/  RFBI_DATA_CYCLE1 (int) ; 
 int /*<<< orphan*/  RFBI_DATA_CYCLE2 (int) ; 
 int /*<<< orphan*/  RFBI_DATA_CYCLE3 (int) ; 
 int /*<<< orphan*/  RFBI_HSYNC_WIDTH ; 
 int /*<<< orphan*/  RFBI_LINE_NUMBER ; 
 int /*<<< orphan*/  RFBI_ONOFF_TIME (int) ; 
 int /*<<< orphan*/  RFBI_PARAM ; 
 int /*<<< orphan*/  RFBI_PIXEL_CNT ; 
 int /*<<< orphan*/  RFBI_READ ; 
 int /*<<< orphan*/  RFBI_REVISION ; 
 int /*<<< orphan*/  RFBI_STATUS ; 
 int /*<<< orphan*/  RFBI_SYSCONFIG ; 
 int /*<<< orphan*/  RFBI_SYSSTATUS ; 
 int /*<<< orphan*/  RFBI_VSYNC_WIDTH ; 
 int /*<<< orphan*/  rfbi_read_reg (int /*<<< orphan*/ ) ; 
 scalar_t__ rfbi_runtime_get () ; 
 int /*<<< orphan*/  rfbi_runtime_put () ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rfbi_dump_regs(struct seq_file *s)
{
#define DUMPREG(r) seq_printf(s, "%-35s %08x\n", #r, rfbi_read_reg(r))

	if (rfbi_runtime_get())
		return;

	DUMPREG(RFBI_REVISION);
	DUMPREG(RFBI_SYSCONFIG);
	DUMPREG(RFBI_SYSSTATUS);
	DUMPREG(RFBI_CONTROL);
	DUMPREG(RFBI_PIXEL_CNT);
	DUMPREG(RFBI_LINE_NUMBER);
	DUMPREG(RFBI_CMD);
	DUMPREG(RFBI_PARAM);
	DUMPREG(RFBI_DATA);
	DUMPREG(RFBI_READ);
	DUMPREG(RFBI_STATUS);

	DUMPREG(RFBI_CONFIG(0));
	DUMPREG(RFBI_ONOFF_TIME(0));
	DUMPREG(RFBI_CYCLE_TIME(0));
	DUMPREG(RFBI_DATA_CYCLE1(0));
	DUMPREG(RFBI_DATA_CYCLE2(0));
	DUMPREG(RFBI_DATA_CYCLE3(0));

	DUMPREG(RFBI_CONFIG(1));
	DUMPREG(RFBI_ONOFF_TIME(1));
	DUMPREG(RFBI_CYCLE_TIME(1));
	DUMPREG(RFBI_DATA_CYCLE1(1));
	DUMPREG(RFBI_DATA_CYCLE2(1));
	DUMPREG(RFBI_DATA_CYCLE3(1));

	DUMPREG(RFBI_VSYNC_WIDTH);
	DUMPREG(RFBI_HSYNC_WIDTH);

	rfbi_runtime_put();
#undef DUMPREG
}