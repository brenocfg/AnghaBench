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
struct xgi_hw_device_info {int jChipType; int /*<<< orphan*/  ulVideoMemorySize; } ;
struct vb_device_info {int ram_channel; int ram_bus; int /*<<< orphan*/  P3c4; int /*<<< orphan*/  P3d4; } ;

/* Variables and functions */
#define  XG20 131 
#define  XG21 130 
#define  XG27 129 
#define  XG42 128 
 int XGINew_CheckFrequence (struct vb_device_info*) ; 
 int XGINew_ReadWriteRest (int,int,struct vb_device_info*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 unsigned char xgifb_reg_get (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xgifb_reg_set (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void XGINew_CheckChannel(struct xgi_hw_device_info *HwDeviceExtension,
				struct vb_device_info *pVBInfo)
{
	unsigned char data;

	switch (HwDeviceExtension->jChipType) {
	case XG20:
	case XG21:
		data = xgifb_reg_get(pVBInfo->P3d4, 0x97);
		data = data & 0x01;
		pVBInfo->ram_channel = 1; /* XG20 "JUST" one channel */

		if (data == 0) { /* Single_32_16 */

			if ((HwDeviceExtension->ulVideoMemorySize - 1)
					> 0x1000000) {
				pVBInfo->ram_bus = 32; /* 32 bits */
				/* 22bit + 2 rank + 32bit */
				xgifb_reg_set(pVBInfo->P3c4, 0x13, 0xB1);
				xgifb_reg_set(pVBInfo->P3c4, 0x14, 0x52);
				usleep_range(15, 1015);

				if (XGINew_ReadWriteRest(24, 23, pVBInfo) == 1)
					return;

				if ((HwDeviceExtension->ulVideoMemorySize - 1) >
				    0x800000) {
					/* 22bit + 1 rank + 32bit */
					xgifb_reg_set(pVBInfo->P3c4,
						      0x13,
						      0x31);
					xgifb_reg_set(pVBInfo->P3c4,
						      0x14,
						      0x42);
					usleep_range(15, 1015);

					if (XGINew_ReadWriteRest(23,
								 23,
								 pVBInfo) == 1)
						return;
				}
			}

			if ((HwDeviceExtension->ulVideoMemorySize - 1) >
			    0x800000) {
				pVBInfo->ram_bus = 16; /* 16 bits */
				/* 22bit + 2 rank + 16bit */
				xgifb_reg_set(pVBInfo->P3c4, 0x13, 0xB1);
				xgifb_reg_set(pVBInfo->P3c4, 0x14, 0x41);
				usleep_range(15, 1015);

				if (XGINew_ReadWriteRest(23, 22, pVBInfo) == 1)
					return;
				xgifb_reg_set(pVBInfo->P3c4,
					      0x13,
					      0x31);
				usleep_range(15, 1015);
			}

		} else { /* Dual_16_8 */
			if ((HwDeviceExtension->ulVideoMemorySize - 1) >
			    0x800000) {
				pVBInfo->ram_bus = 16; /* 16 bits */
				/* (0x31:12x8x2) 22bit + 2 rank */
				xgifb_reg_set(pVBInfo->P3c4, 0x13, 0xB1);
				/* 0x41:16Mx16 bit */
				xgifb_reg_set(pVBInfo->P3c4, 0x14, 0x41);
				usleep_range(15, 1015);

				if (XGINew_ReadWriteRest(23, 22, pVBInfo) == 1)
					return;

				if ((HwDeviceExtension->ulVideoMemorySize - 1) >
				    0x400000) {
					/* (0x31:12x8x2) 22bit + 1 rank */
					xgifb_reg_set(pVBInfo->P3c4,
						      0x13,
						      0x31);
					/* 0x31:8Mx16 bit */
					xgifb_reg_set(pVBInfo->P3c4,
						      0x14,
						      0x31);
					usleep_range(15, 1015);

					if (XGINew_ReadWriteRest(22,
								 22,
								 pVBInfo) == 1)
						return;
				}
			}

			if ((HwDeviceExtension->ulVideoMemorySize - 1) >
			    0x400000) {
				pVBInfo->ram_bus = 8; /* 8 bits */
				/* (0x31:12x8x2) 22bit + 2 rank */
				xgifb_reg_set(pVBInfo->P3c4, 0x13, 0xB1);
				/* 0x30:8Mx8 bit */
				xgifb_reg_set(pVBInfo->P3c4, 0x14, 0x30);
				usleep_range(15, 1015);

				if (XGINew_ReadWriteRest(22, 21, pVBInfo) == 1)
					return;

				/* (0x31:12x8x2) 22bit + 1 rank */
				xgifb_reg_set(pVBInfo->P3c4,
					      0x13,
					      0x31);
				usleep_range(15, 1015);
			}
		}
		break;

	case XG27:
		pVBInfo->ram_bus = 16; /* 16 bits */
		pVBInfo->ram_channel = 1; /* Single channel */
		xgifb_reg_set(pVBInfo->P3c4, 0x14, 0x51); /* 32Mx16 bit */
		break;
	case XG42:
		/*
		 * XG42 SR14 D[3] Reserve
		 * D[2] = 1, Dual Channel
		 * = 0, Single Channel
		 *
		 * It's Different from Other XG40 Series.
		 */
		if (XGINew_CheckFrequence(pVBInfo) == 1) { /* DDRII, DDR2x */
			pVBInfo->ram_bus = 32; /* 32 bits */
			pVBInfo->ram_channel = 2; /* 2 Channel */
			xgifb_reg_set(pVBInfo->P3c4, 0x13, 0xA1);
			xgifb_reg_set(pVBInfo->P3c4, 0x14, 0x44);

			if (XGINew_ReadWriteRest(24, 23, pVBInfo) == 1)
				return;

			xgifb_reg_set(pVBInfo->P3c4, 0x13, 0x21);
			xgifb_reg_set(pVBInfo->P3c4, 0x14, 0x34);
			if (XGINew_ReadWriteRest(23, 22, pVBInfo) == 1)
				return;

			pVBInfo->ram_channel = 1; /* Single Channel */
			xgifb_reg_set(pVBInfo->P3c4, 0x13, 0xA1);
			xgifb_reg_set(pVBInfo->P3c4, 0x14, 0x40);

			if (XGINew_ReadWriteRest(23, 22, pVBInfo) == 1)
				return;
			xgifb_reg_set(pVBInfo->P3c4, 0x13, 0x21);
			xgifb_reg_set(pVBInfo->P3c4, 0x14, 0x30);
		} else { /* DDR */
			pVBInfo->ram_bus = 64; /* 64 bits */
			pVBInfo->ram_channel = 1; /* 1 channels */
			xgifb_reg_set(pVBInfo->P3c4, 0x13, 0xA1);
			xgifb_reg_set(pVBInfo->P3c4, 0x14, 0x52);

			if (XGINew_ReadWriteRest(24, 23, pVBInfo) == 1)
				return;
			xgifb_reg_set(pVBInfo->P3c4, 0x13, 0x21);
			xgifb_reg_set(pVBInfo->P3c4, 0x14, 0x42);
		}

		break;

	default: /* XG40 */

		if (XGINew_CheckFrequence(pVBInfo) == 1) { /* DDRII */
			pVBInfo->ram_bus = 32; /* 32 bits */
			pVBInfo->ram_channel = 3;
			xgifb_reg_set(pVBInfo->P3c4, 0x13, 0xA1);
			xgifb_reg_set(pVBInfo->P3c4, 0x14, 0x4C);

			if (XGINew_ReadWriteRest(25, 23, pVBInfo) == 1)
				return;

			pVBInfo->ram_channel = 2; /* 2 channels */
			xgifb_reg_set(pVBInfo->P3c4, 0x14, 0x48);

			if (XGINew_ReadWriteRest(24, 23, pVBInfo) == 1)
				return;

			xgifb_reg_set(pVBInfo->P3c4, 0x13, 0x21);
			xgifb_reg_set(pVBInfo->P3c4, 0x14, 0x3C);

			if (XGINew_ReadWriteRest(24, 23, pVBInfo) == 1) {
				pVBInfo->ram_channel = 3; /* 4 channels */
			} else {
				pVBInfo->ram_channel = 2; /* 2 channels */
				xgifb_reg_set(pVBInfo->P3c4, 0x14, 0x38);
			}
		} else { /* DDR */
			pVBInfo->ram_bus = 64; /* 64 bits */
			pVBInfo->ram_channel = 2; /* 2 channels */
			xgifb_reg_set(pVBInfo->P3c4, 0x13, 0xA1);
			xgifb_reg_set(pVBInfo->P3c4, 0x14, 0x5A);

			if (XGINew_ReadWriteRest(25, 24, pVBInfo) == 1)
				return;
			xgifb_reg_set(pVBInfo->P3c4, 0x13, 0x21);
			xgifb_reg_set(pVBInfo->P3c4, 0x14, 0x4A);
		}
		break;
	}
}