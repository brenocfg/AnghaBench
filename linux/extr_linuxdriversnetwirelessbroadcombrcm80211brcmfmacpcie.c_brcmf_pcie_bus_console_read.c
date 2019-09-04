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
typedef  char u8 ;
typedef  scalar_t__ u32 ;
struct brcmf_pcie_console {scalar_t__ base_addr; scalar_t__ read_idx; scalar_t__ buf_addr; scalar_t__ bufsize; char* log_str; size_t log_idx; } ;
struct TYPE_2__ {struct brcmf_pcie_console console; } ;
struct brcmf_pciedev_info {TYPE_1__ shared; } ;

/* Variables and functions */
 scalar_t__ BRCMF_CONSOLE_WRITEIDX_OFFSET ; 
 int /*<<< orphan*/  BRCMF_FWCON_ON () ; 
 scalar_t__ brcmf_pcie_read_tcm32 (struct brcmf_pciedev_info*,scalar_t__) ; 
 char brcmf_pcie_read_tcm8 (struct brcmf_pciedev_info*,scalar_t__) ; 
 int /*<<< orphan*/  pr_debug (char*,char*) ; 

__attribute__((used)) static void brcmf_pcie_bus_console_read(struct brcmf_pciedev_info *devinfo)
{
	struct brcmf_pcie_console *console;
	u32 addr;
	u8 ch;
	u32 newidx;

	if (!BRCMF_FWCON_ON())
		return;

	console = &devinfo->shared.console;
	addr = console->base_addr + BRCMF_CONSOLE_WRITEIDX_OFFSET;
	newidx = brcmf_pcie_read_tcm32(devinfo, addr);
	while (newidx != console->read_idx) {
		addr = console->buf_addr + console->read_idx;
		ch = brcmf_pcie_read_tcm8(devinfo, addr);
		console->read_idx++;
		if (console->read_idx == console->bufsize)
			console->read_idx = 0;
		if (ch == '\r')
			continue;
		console->log_str[console->log_idx] = ch;
		console->log_idx++;
		if ((ch != '\n') &&
		    (console->log_idx == (sizeof(console->log_str) - 2))) {
			ch = '\n';
			console->log_str[console->log_idx] = ch;
			console->log_idx++;
		}
		if (ch == '\n') {
			console->log_str[console->log_idx] = 0;
			pr_debug("CONSOLE: %s", console->log_str);
			console->log_idx = 0;
		}
	}
}