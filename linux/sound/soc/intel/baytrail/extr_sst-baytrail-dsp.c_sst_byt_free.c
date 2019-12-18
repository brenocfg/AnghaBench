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
struct TYPE_2__ {int /*<<< orphan*/  fw_ext; int /*<<< orphan*/  pci_cfg; int /*<<< orphan*/  lpe; } ;
struct sst_dsp {TYPE_1__ addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sst_mem_block_unregister_all (struct sst_dsp*) ; 

__attribute__((used)) static void sst_byt_free(struct sst_dsp *sst)
{
	sst_mem_block_unregister_all(sst);
	iounmap(sst->addr.lpe);
	iounmap(sst->addr.pci_cfg);
	iounmap(sst->addr.fw_ext);
}