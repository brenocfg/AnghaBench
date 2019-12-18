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
typedef  int u8 ;
typedef  int u16 ;
struct TYPE_2__ {int /*<<< orphan*/  (* write ) (struct snd_wm8776*,int,int) ;} ;
struct snd_wm8776 {int* regs; TYPE_1__ ops; } ;

/* Variables and functions */
 int WM8776_REG_RESET ; 
 int /*<<< orphan*/  stub1 (struct snd_wm8776*,int,int) ; 

__attribute__((used)) static void snd_wm8776_write(struct snd_wm8776 *wm, u16 addr, u16 data)
{
	u8 bus_addr = addr << 1 | data >> 8;	/* addr + 9th data bit */
	u8 bus_data = data & 0xff;		/* remaining 8 data bits */

	if (addr < WM8776_REG_RESET)
		wm->regs[addr] = data;
	wm->ops.write(wm, bus_addr, bus_data);
}