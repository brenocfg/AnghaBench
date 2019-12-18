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
struct sonicvibes {scalar_t__ dmaa_port; TYPE_1__* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ SV_DMA_ADDR0 ; 
 scalar_t__ SV_DMA_COUNT0 ; 
 scalar_t__ SV_DMA_MODE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inl (scalar_t__) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  outl (unsigned int,scalar_t__) ; 

__attribute__((used)) static inline void snd_sonicvibes_setdmaa(struct sonicvibes * sonic,
					  unsigned int addr,
					  unsigned int count)
{
	count--;
	outl(addr, sonic->dmaa_port + SV_DMA_ADDR0);
	outl(count, sonic->dmaa_port + SV_DMA_COUNT0);
	outb(0x18, sonic->dmaa_port + SV_DMA_MODE);
#if 0
	dev_dbg(sonic->card->dev, "program dmaa: addr = 0x%x, paddr = 0x%x\n",
	       addr, inl(sonic->dmaa_port + SV_DMA_ADDR0));
#endif
}