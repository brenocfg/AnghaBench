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
struct seq_file {int /*<<< orphan*/  private; } ;
struct brcmf_rev_info {int /*<<< orphan*/  nvramrev; int /*<<< orphan*/  anarev; int /*<<< orphan*/  phyrev; int /*<<< orphan*/  phytype; int /*<<< orphan*/  bus; int /*<<< orphan*/  ucoderev; int /*<<< orphan*/  driverrev; int /*<<< orphan*/  boardrev; int /*<<< orphan*/  boardvendor; int /*<<< orphan*/  boardid; int /*<<< orphan*/  corerev; int /*<<< orphan*/  chippkg; int /*<<< orphan*/  chipname; int /*<<< orphan*/  radiorev; int /*<<< orphan*/  deviceid; int /*<<< orphan*/  vendorid; } ;
struct brcmf_bus {TYPE_1__* drvr; } ;
struct TYPE_2__ {int /*<<< orphan*/  clmver; struct brcmf_rev_info revinfo; } ;

/* Variables and functions */
 int BRCMU_BOARDREV_LEN ; 
 int BRCMU_DOTREV_LEN ; 
 int /*<<< orphan*/  brcmu_boardrev_str (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  brcmu_dotrev_str (int /*<<< orphan*/ ,char*) ; 
 struct brcmf_bus* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int brcmf_revinfo_read(struct seq_file *s, void *data)
{
	struct brcmf_bus *bus_if = dev_get_drvdata(s->private);
	struct brcmf_rev_info *ri = &bus_if->drvr->revinfo;
	char drev[BRCMU_DOTREV_LEN];
	char brev[BRCMU_BOARDREV_LEN];

	seq_printf(s, "vendorid: 0x%04x\n", ri->vendorid);
	seq_printf(s, "deviceid: 0x%04x\n", ri->deviceid);
	seq_printf(s, "radiorev: %s\n", brcmu_dotrev_str(ri->radiorev, drev));
	seq_printf(s, "chip: %s\n", ri->chipname);
	seq_printf(s, "chippkg: %u\n", ri->chippkg);
	seq_printf(s, "corerev: %u\n", ri->corerev);
	seq_printf(s, "boardid: 0x%04x\n", ri->boardid);
	seq_printf(s, "boardvendor: 0x%04x\n", ri->boardvendor);
	seq_printf(s, "boardrev: %s\n", brcmu_boardrev_str(ri->boardrev, brev));
	seq_printf(s, "driverrev: %s\n", brcmu_dotrev_str(ri->driverrev, drev));
	seq_printf(s, "ucoderev: %u\n", ri->ucoderev);
	seq_printf(s, "bus: %u\n", ri->bus);
	seq_printf(s, "phytype: %u\n", ri->phytype);
	seq_printf(s, "phyrev: %u\n", ri->phyrev);
	seq_printf(s, "anarev: %u\n", ri->anarev);
	seq_printf(s, "nvramrev: %08x\n", ri->nvramrev);

	seq_printf(s, "clmver: %s\n", bus_if->drvr->clmver);

	return 0;
}