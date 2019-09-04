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
struct hpc3_regs {int /*<<< orphan*/ * pbdma; } ;
struct TYPE_2__ {int pbusnr; int /*<<< orphan*/ * pbus; } ;
struct hal2_codec {TYPE_1__ pbus; } ;

/* Variables and functions */

__attribute__((used)) static void hal2_init_codec(struct hal2_codec *codec, struct hpc3_regs *hpc3,
			    int index)
{
	codec->pbus.pbusnr = index;
	codec->pbus.pbus = &hpc3->pbdma[index];
}