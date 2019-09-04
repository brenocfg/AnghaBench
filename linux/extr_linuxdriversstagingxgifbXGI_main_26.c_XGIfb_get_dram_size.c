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
typedef  int u8 ;
struct vb_device_info {int /*<<< orphan*/  P3c4; } ;
struct xgifb_video_info {int chip; int video_size; struct vb_device_info dev_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  IND_SIS_DRAM_SIZE ; 
#define  XG20 141 
#define  XG21 140 
#define  XG27 139 
#define  XG40 138 
#define  XG42 137 
#define  XGI_DRAM_SIZE_128MB 136 
#define  XGI_DRAM_SIZE_16MB 135 
#define  XGI_DRAM_SIZE_1MB 134 
#define  XGI_DRAM_SIZE_256MB 133 
#define  XGI_DRAM_SIZE_2MB 132 
#define  XGI_DRAM_SIZE_32MB 131 
#define  XGI_DRAM_SIZE_4MB 130 
#define  XGI_DRAM_SIZE_64MB 129 
#define  XGI_DRAM_SIZE_8MB 128 
 int XGI_DRAM_SIZE_MASK ; 
 int /*<<< orphan*/  pr_info (char*,int,int,int) ; 
 int xgifb_reg_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xgifb_reg_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int XGIfb_get_dram_size(struct xgifb_video_info *xgifb_info)
{
	struct vb_device_info *vb = &xgifb_info->dev_info;
	u8 ChannelNum, tmp;
	u8 reg = 0;

	/* xorg driver sets 32MB * 1 channel */
	if (xgifb_info->chip == XG27)
		xgifb_reg_set(vb->P3c4, IND_SIS_DRAM_SIZE, 0x51);

	reg = xgifb_reg_get(vb->P3c4, IND_SIS_DRAM_SIZE);
	if (!reg)
		return -1;

	switch ((reg & XGI_DRAM_SIZE_MASK) >> 4) {
	case XGI_DRAM_SIZE_1MB:
		xgifb_info->video_size = 0x100000;
		break;
	case XGI_DRAM_SIZE_2MB:
		xgifb_info->video_size = 0x200000;
		break;
	case XGI_DRAM_SIZE_4MB:
		xgifb_info->video_size = 0x400000;
		break;
	case XGI_DRAM_SIZE_8MB:
		xgifb_info->video_size = 0x800000;
		break;
	case XGI_DRAM_SIZE_16MB:
		xgifb_info->video_size = 0x1000000;
		break;
	case XGI_DRAM_SIZE_32MB:
		xgifb_info->video_size = 0x2000000;
		break;
	case XGI_DRAM_SIZE_64MB:
		xgifb_info->video_size = 0x4000000;
		break;
	case XGI_DRAM_SIZE_128MB:
		xgifb_info->video_size = 0x8000000;
		break;
	case XGI_DRAM_SIZE_256MB:
		xgifb_info->video_size = 0x10000000;
		break;
	default:
		return -1;
	}

	tmp = (reg & 0x0c) >> 2;
	switch (xgifb_info->chip) {
	case XG20:
	case XG21:
	case XG27:
		ChannelNum = 1;
		break;

	case XG42:
		if (reg & 0x04)
			ChannelNum = 2;
		else
			ChannelNum = 1;
		break;

	case XG40:
	default:
		if (tmp == 2)
			ChannelNum = 2;
		else if (tmp == 3)
			ChannelNum = 3;
		else
			ChannelNum = 1;
		break;
	}

	xgifb_info->video_size = xgifb_info->video_size * ChannelNum;

	pr_info("SR14=%x DramSzie %x ChannelNum %x\n",
		reg, xgifb_info->video_size, ChannelNum);
	return 0;
}