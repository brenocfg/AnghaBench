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
typedef  int /*<<< orphan*/  u32 ;
struct seq_file {struct dwc3* private; } ;
struct dwc3 {int /*<<< orphan*/  lock; int /*<<< orphan*/  regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC3_GCTL ; 
 int DWC3_GCTL_PRTCAP (int /*<<< orphan*/ ) ; 
#define  DWC3_GCTL_PRTCAP_DEVICE 130 
#define  DWC3_GCTL_PRTCAP_HOST 129 
#define  DWC3_GCTL_PRTCAP_OTG 128 
 int /*<<< orphan*/  dwc3_readl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int dwc3_mode_show(struct seq_file *s, void *unused)
{
	struct dwc3		*dwc = s->private;
	unsigned long		flags;
	u32			reg;

	spin_lock_irqsave(&dwc->lock, flags);
	reg = dwc3_readl(dwc->regs, DWC3_GCTL);
	spin_unlock_irqrestore(&dwc->lock, flags);

	switch (DWC3_GCTL_PRTCAP(reg)) {
	case DWC3_GCTL_PRTCAP_HOST:
		seq_printf(s, "host\n");
		break;
	case DWC3_GCTL_PRTCAP_DEVICE:
		seq_printf(s, "device\n");
		break;
	case DWC3_GCTL_PRTCAP_OTG:
		seq_printf(s, "otg\n");
		break;
	default:
		seq_printf(s, "UNKNOWN %08x\n", DWC3_GCTL_PRTCAP(reg));
	}

	return 0;
}