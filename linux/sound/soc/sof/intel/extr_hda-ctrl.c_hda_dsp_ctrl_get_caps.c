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
typedef  int u32 ;
struct snd_sof_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/ * bar; } ;
struct hdac_bus {int /*<<< orphan*/  remap_addr; int /*<<< orphan*/  mlcap; int /*<<< orphan*/  gtscap; int /*<<< orphan*/  drsmcap; int /*<<< orphan*/  spbcap; int /*<<< orphan*/  ppcap; } ;

/* Variables and functions */
 size_t HDA_DSP_DRSM_BAR ; 
 int /*<<< orphan*/  HDA_DSP_HDA_BAR ; 
 size_t HDA_DSP_PP_BAR ; 
 size_t HDA_DSP_SPIB_BAR ; 
 int SOF_HDA_CAP_ID_MASK ; 
 int SOF_HDA_CAP_ID_OFF ; 
 int SOF_HDA_CAP_NEXT_MASK ; 
#define  SOF_HDA_DRSM_CAP_ID 132 
#define  SOF_HDA_GTS_CAP_ID 131 
 int SOF_HDA_LLCH ; 
 int /*<<< orphan*/  SOF_HDA_MAX_CAPS ; 
#define  SOF_HDA_ML_CAP_ID 130 
#define  SOF_HDA_PP_CAP_ID 129 
#define  SOF_HDA_SPIB_CAP_ID 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ ,char*,int,int) ; 
 int snd_sof_dsp_read (struct snd_sof_dev*,int /*<<< orphan*/ ,int) ; 
 struct hdac_bus* sof_to_bus (struct snd_sof_dev*) ; 

int hda_dsp_ctrl_get_caps(struct snd_sof_dev *sdev)
{
	struct hdac_bus *bus = sof_to_bus(sdev);
	u32 cap, offset, feature;
	int count = 0;

	offset = snd_sof_dsp_read(sdev, HDA_DSP_HDA_BAR, SOF_HDA_LLCH);

	do {
		cap = snd_sof_dsp_read(sdev, HDA_DSP_HDA_BAR, offset);

		dev_dbg(sdev->dev, "checking for capabilities at offset 0x%x\n",
			offset & SOF_HDA_CAP_NEXT_MASK);

		feature = (cap & SOF_HDA_CAP_ID_MASK) >> SOF_HDA_CAP_ID_OFF;

		switch (feature) {
		case SOF_HDA_PP_CAP_ID:
			dev_dbg(sdev->dev, "found DSP capability at 0x%x\n",
				offset);
			bus->ppcap = bus->remap_addr + offset;
			sdev->bar[HDA_DSP_PP_BAR] = bus->ppcap;
			break;
		case SOF_HDA_SPIB_CAP_ID:
			dev_dbg(sdev->dev, "found SPIB capability at 0x%x\n",
				offset);
			bus->spbcap = bus->remap_addr + offset;
			sdev->bar[HDA_DSP_SPIB_BAR] = bus->spbcap;
			break;
		case SOF_HDA_DRSM_CAP_ID:
			dev_dbg(sdev->dev, "found DRSM capability at 0x%x\n",
				offset);
			bus->drsmcap = bus->remap_addr + offset;
			sdev->bar[HDA_DSP_DRSM_BAR] = bus->drsmcap;
			break;
		case SOF_HDA_GTS_CAP_ID:
			dev_dbg(sdev->dev, "found GTS capability at 0x%x\n",
				offset);
			bus->gtscap = bus->remap_addr + offset;
			break;
		case SOF_HDA_ML_CAP_ID:
			dev_dbg(sdev->dev, "found ML capability at 0x%x\n",
				offset);
			bus->mlcap = bus->remap_addr + offset;
			break;
		default:
			dev_vdbg(sdev->dev, "found capability %d at 0x%x\n",
				 feature, offset);
			break;
		}

		offset = cap & SOF_HDA_CAP_NEXT_MASK;
	} while (count++ <= SOF_HDA_MAX_CAPS && offset);

	return 0;
}