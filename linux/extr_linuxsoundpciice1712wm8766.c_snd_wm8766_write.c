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
typedef  size_t u16 ;
struct TYPE_2__ {int /*<<< orphan*/  (* write ) (struct snd_wm8766*,size_t,size_t) ;} ;
struct snd_wm8766 {size_t* regs; TYPE_1__ ops; } ;

/* Variables and functions */
 size_t WM8766_REG_COUNT ; 
 int /*<<< orphan*/  stub1 (struct snd_wm8766*,size_t,size_t) ; 

__attribute__((used)) static void snd_wm8766_write(struct snd_wm8766 *wm, u16 addr, u16 data)
{
	if (addr < WM8766_REG_COUNT)
		wm->regs[addr] = data;
	wm->ops.write(wm, addr, data);
}