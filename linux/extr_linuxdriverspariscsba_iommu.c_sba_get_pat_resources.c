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
struct sba_device {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void
sba_get_pat_resources(struct sba_device *sba_dev)
{
#if 0
/*
** TODO/REVISIT/FIXME: support for directed ranges requires calls to
**      PAT PDC to program the SBA/LBA directed range registers...this
**      burden may fall on the LBA code since it directly supports the
**      PCI subsystem. It's not clear yet. - ggg
*/
PAT_MOD(mod)->mod_info.mod_pages   = PAT_GET_MOD_PAGES(temp);
	FIXME : ???
PAT_MOD(mod)->mod_info.dvi         = PAT_GET_DVI(temp);
	Tells where the dvi bits are located in the address.
PAT_MOD(mod)->mod_info.ioc         = PAT_GET_IOC(temp);
	FIXME : ???
#endif
}