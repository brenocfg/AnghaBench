#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  mmio; TYPE_1__* card; } ;
typedef  TYPE_2__ vortex_t ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int VORTEX_SRCBLOCK_SR ; 
 unsigned char VORTEX_SRC_CHNBASE ; 
 unsigned char VORTEX_SRC_RTBASE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int hwread (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hwwrite (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  vortex_src_dis_sr (TYPE_2__*,unsigned char) ; 

__attribute__((used)) static int
vortex_src_delWTD(vortex_t * vortex, unsigned char src, unsigned char ch)
{
	int esp14 = -1, esp18, eax, ebx, edx, ebp, esi = 0;
	//int esp1f=edi(while)=src, esp10=ch;

	eax = hwread(vortex->mmio, VORTEX_SRCBLOCK_SR);
	if (((1 << ch) & eax) == 0) {
		dev_err(vortex->card->dev, "src alarm\n");
		return 0;
	}
	ebp = VORTEX_SRC_CHNBASE + (ch << 2);
	esp18 = hwread(vortex->mmio, ebp);
	if (esp18 & 0x10) {
		ebx = (esp18 & 0xf);
		if (src == ebx) {
			ebx = VORTEX_SRC_RTBASE + (src << 2);
			edx = hwread(vortex->mmio, ebx);
			//7b60
			hwwrite(vortex->mmio, ebp, edx);
			hwwrite(vortex->mmio, ebx, 0);
		} else {
			//7ad3
			edx =
			    hwread(vortex->mmio,
				   VORTEX_SRC_RTBASE + (ebx << 2));
			//printk(KERN_INFO "vortex: srcdelWTD: 1 addr=%x, val=%x, src=%x\n", ebx, edx, src);
			while ((edx & 0xf) != src) {
				if ((esi) > 0xf) {
					dev_warn(vortex->card->dev,
						 "srcdelWTD: error, lifeboat overflow\n");
					return 0;
				}
				esp14 = ebx;
				ebx = edx & 0xf;
				ebp = ebx << 2;
				edx =
				    hwread(vortex->mmio,
					   VORTEX_SRC_RTBASE + ebp);
				//printk(KERN_INFO "vortex: srcdelWTD: while addr=%x, val=%x\n", ebp, edx);
				esi++;
			}
			//7b30
			ebp = ebx << 2;
			if (edx & 0x10) {	/* Delete entry in between others */
				ebx = VORTEX_SRC_RTBASE + ((edx & 0xf) << 2);
				edx = hwread(vortex->mmio, ebx);
				//7b60
				hwwrite(vortex->mmio,
					VORTEX_SRC_RTBASE + ebp, edx);
				hwwrite(vortex->mmio, ebx, 0);
				//printk(KERN_INFO "vortex srcdelWTD between addr= 0x%x, val= 0x%x\n", ebp, edx);
			} else {	/* Delete last entry */
				//7b83
				if (esp14 == -1)
					hwwrite(vortex->mmio,
						VORTEX_SRC_CHNBASE +
						(ch << 2), esp18 & 0xef);
				else {
					ebx = (0xffffffe0 & edx) | (0xf & ebx);
					hwwrite(vortex->mmio,
						VORTEX_SRC_RTBASE +
						(esp14 << 2), ebx);
					//printk(KERN_INFO"vortex srcdelWTD last addr= 0x%x, val= 0x%x\n", esp14, ebx);
				}
				hwwrite(vortex->mmio,
					VORTEX_SRC_RTBASE + ebp, 0);
				return 1;
			}
		}
	} else {
		//7be0
		vortex_src_dis_sr(vortex, ch);
		hwwrite(vortex->mmio, ebp, 0);
	}
	return 1;
}