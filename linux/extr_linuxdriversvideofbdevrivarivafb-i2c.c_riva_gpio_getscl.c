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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  PCIO; } ;
struct riva_par {TYPE_1__ riva; } ;
struct riva_i2c_chan {int /*<<< orphan*/  ddc_base; struct riva_par* par; } ;

/* Variables and functions */
 int VGA_RD08 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  VGA_WR08 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int riva_gpio_getscl(void* data)
{
	struct riva_i2c_chan 	*chan = data;
	struct riva_par 	*par = chan->par;
	u32			val = 0;

	VGA_WR08(par->riva.PCIO, 0x3d4, chan->ddc_base);
	if (VGA_RD08(par->riva.PCIO, 0x3d5) & 0x04)
		val = 1;

	return val;
}