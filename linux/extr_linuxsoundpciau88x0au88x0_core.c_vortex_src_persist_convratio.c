#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* card; int /*<<< orphan*/  mmio; } ;
typedef  TYPE_2__ vortex_t ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ VORTEX_SRC_CONVRATIO ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int hwread (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  hwwrite (int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static int
vortex_src_persist_convratio(vortex_t * vortex, unsigned char src, int ratio)
{
	int temp, lifeboat = 0;

	do {
		hwwrite(vortex->mmio, VORTEX_SRC_CONVRATIO + (src << 2), ratio);
		temp = hwread(vortex->mmio, VORTEX_SRC_CONVRATIO + (src << 2));
		if ((++lifeboat) > 0x9) {
			dev_err(vortex->card->dev, "Src cvr fail\n");
			break;
		}
	}
	while (temp != ratio);
	return temp;
}