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
struct TYPE_2__ {int rate; } ;

/* Variables and functions */
 TYPE_1__* skl_clk_src ; 

__attribute__((used)) static void init_skl_xtal_rate(int pci_id)
{
	switch (pci_id) {
	case 0x9d70:
	case 0x9d71:
		skl_clk_src[0].rate = 24000000;
		return;

	default:
		skl_clk_src[0].rate = 19200000;
		return;
	}
}