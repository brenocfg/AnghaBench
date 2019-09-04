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
struct snd_kcontrol {int private_value; } ;
struct snd_ctl_elem_info {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  member; } ;

/* Variables and functions */
 int EINVAL ; 
 TYPE_1__* se200pci_cont ; 
 int se200pci_get_enum_count (int) ; 
 int snd_ctl_enum_info (struct snd_ctl_elem_info*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int se200pci_cont_enum_info(struct snd_kcontrol *kc,
				   struct snd_ctl_elem_info *uinfo)
{
	int n, c;

	n = kc->private_value;
	c = se200pci_get_enum_count(n);
	if (!c)
		return -EINVAL;
	return snd_ctl_enum_info(uinfo, 1, c, se200pci_cont[n].member);
}