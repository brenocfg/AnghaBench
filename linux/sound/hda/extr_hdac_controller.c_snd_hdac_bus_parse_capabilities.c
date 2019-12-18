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
struct hdac_bus {int /*<<< orphan*/  dev; int /*<<< orphan*/  remap_addr; int /*<<< orphan*/  drsmcap; int /*<<< orphan*/  spbcap; int /*<<< orphan*/  ppcap; int /*<<< orphan*/  gtscap; int /*<<< orphan*/  mlcap; } ;

/* Variables and functions */
 unsigned int AZX_CAP_HDR_ID_MASK ; 
 unsigned int AZX_CAP_HDR_ID_OFF ; 
 unsigned int AZX_CAP_HDR_NXT_PTR_MASK ; 
 unsigned int AZX_CAP_HDR_VER_MASK ; 
 unsigned int AZX_CAP_HDR_VER_OFF ; 
#define  AZX_DRSM_CAP_ID 132 
#define  AZX_GTS_CAP_ID 131 
#define  AZX_ML_CAP_ID 130 
#define  AZX_PP_CAP_ID 129 
#define  AZX_SPB_CAP_ID 128 
 unsigned int HDAC_MAX_CAPS ; 
 int /*<<< orphan*/  LLCH ; 
 unsigned int _snd_hdac_chip_readl (struct hdac_bus*,unsigned int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 unsigned int snd_hdac_chip_readw (struct hdac_bus*,int /*<<< orphan*/ ) ; 

int snd_hdac_bus_parse_capabilities(struct hdac_bus *bus)
{
	unsigned int cur_cap;
	unsigned int offset;
	unsigned int counter = 0;

	offset = snd_hdac_chip_readw(bus, LLCH);

	/* Lets walk the linked capabilities list */
	do {
		cur_cap = _snd_hdac_chip_readl(bus, offset);

		dev_dbg(bus->dev, "Capability version: 0x%x\n",
			(cur_cap & AZX_CAP_HDR_VER_MASK) >> AZX_CAP_HDR_VER_OFF);

		dev_dbg(bus->dev, "HDA capability ID: 0x%x\n",
			(cur_cap & AZX_CAP_HDR_ID_MASK) >> AZX_CAP_HDR_ID_OFF);

		if (cur_cap == -1) {
			dev_dbg(bus->dev, "Invalid capability reg read\n");
			break;
		}

		switch ((cur_cap & AZX_CAP_HDR_ID_MASK) >> AZX_CAP_HDR_ID_OFF) {
		case AZX_ML_CAP_ID:
			dev_dbg(bus->dev, "Found ML capability\n");
			bus->mlcap = bus->remap_addr + offset;
			break;

		case AZX_GTS_CAP_ID:
			dev_dbg(bus->dev, "Found GTS capability offset=%x\n", offset);
			bus->gtscap = bus->remap_addr + offset;
			break;

		case AZX_PP_CAP_ID:
			/* PP capability found, the Audio DSP is present */
			dev_dbg(bus->dev, "Found PP capability offset=%x\n", offset);
			bus->ppcap = bus->remap_addr + offset;
			break;

		case AZX_SPB_CAP_ID:
			/* SPIB capability found, handler function */
			dev_dbg(bus->dev, "Found SPB capability\n");
			bus->spbcap = bus->remap_addr + offset;
			break;

		case AZX_DRSM_CAP_ID:
			/* DMA resume  capability found, handler function */
			dev_dbg(bus->dev, "Found DRSM capability\n");
			bus->drsmcap = bus->remap_addr + offset;
			break;

		default:
			dev_err(bus->dev, "Unknown capability %d\n", cur_cap);
			cur_cap = 0;
			break;
		}

		counter++;

		if (counter > HDAC_MAX_CAPS) {
			dev_err(bus->dev, "We exceeded HDAC capabilities!!!\n");
			break;
		}

		/* read the offset of next capability */
		offset = cur_cap & AZX_CAP_HDR_NXT_PTR_MASK;

	} while (offset);

	return 0;
}