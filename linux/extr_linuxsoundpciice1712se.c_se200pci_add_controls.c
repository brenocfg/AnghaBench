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
struct TYPE_4__ {int /*<<< orphan*/ * p; } ;
struct snd_kcontrol_new {int private_value; int /*<<< orphan*/  put; int /*<<< orphan*/  get; int /*<<< orphan*/  info; TYPE_1__ tlv; int /*<<< orphan*/  access; int /*<<< orphan*/  name; int /*<<< orphan*/  iface; } ;
struct snd_ice1712 {int /*<<< orphan*/  card; } ;
typedef  int /*<<< orphan*/  cont ;
struct TYPE_5__ {int type; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_2__*) ; 
#define  BOOLEAN 131 
 int EINVAL ; 
#define  ENUM 130 
 int /*<<< orphan*/  SNDRV_CTL_ELEM_ACCESS_READWRITE ; 
 int /*<<< orphan*/  SNDRV_CTL_ELEM_ACCESS_TLV_READ ; 
 int /*<<< orphan*/  SNDRV_CTL_ELEM_IFACE_MIXER ; 
#define  VOLUME1 129 
#define  VOLUME2 128 
 int /*<<< orphan*/ * db_scale_gain1 ; 
 int /*<<< orphan*/ * db_scale_gain2 ; 
 int /*<<< orphan*/  memset (struct snd_kcontrol_new*,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* se200pci_cont ; 
 int /*<<< orphan*/  se200pci_cont_boolean_get ; 
 int /*<<< orphan*/  se200pci_cont_boolean_info ; 
 int /*<<< orphan*/  se200pci_cont_boolean_put ; 
 int /*<<< orphan*/  se200pci_cont_enum_get ; 
 int /*<<< orphan*/  se200pci_cont_enum_info ; 
 int /*<<< orphan*/  se200pci_cont_enum_put ; 
 int /*<<< orphan*/  se200pci_cont_volume_get ; 
 int /*<<< orphan*/  se200pci_cont_volume_info ; 
 int /*<<< orphan*/  se200pci_cont_volume_put ; 
 int /*<<< orphan*/  snd_BUG () ; 
 int snd_ctl_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ctl_new1 (struct snd_kcontrol_new*,struct snd_ice1712*) ; 

__attribute__((used)) static int se200pci_add_controls(struct snd_ice1712 *ice)
{
	int i;
	struct snd_kcontrol_new cont;
	int err;

	memset(&cont, 0, sizeof(cont));
	cont.iface = SNDRV_CTL_ELEM_IFACE_MIXER;
	for (i = 0; i < ARRAY_SIZE(se200pci_cont); i++) {
		cont.private_value = i;
		cont.name = se200pci_cont[i].name;
		cont.access = SNDRV_CTL_ELEM_ACCESS_READWRITE;
		cont.tlv.p = NULL;
		switch (se200pci_cont[i].type) {
		case VOLUME1:
		case VOLUME2:
			cont.info = se200pci_cont_volume_info;
			cont.get = se200pci_cont_volume_get;
			cont.put = se200pci_cont_volume_put;
			cont.access |= SNDRV_CTL_ELEM_ACCESS_TLV_READ;
			if (se200pci_cont[i].type == VOLUME1)
				cont.tlv.p = db_scale_gain1;
			else
				cont.tlv.p = db_scale_gain2;
			break;
		case BOOLEAN:
			cont.info = se200pci_cont_boolean_info;
			cont.get = se200pci_cont_boolean_get;
			cont.put = se200pci_cont_boolean_put;
			break;
		case ENUM:
			cont.info = se200pci_cont_enum_info;
			cont.get = se200pci_cont_enum_get;
			cont.put = se200pci_cont_enum_put;
			break;
		default:
			snd_BUG();
			return -EINVAL;
		}
		err = snd_ctl_add(ice->card, snd_ctl_new1(&cont, ice));
		if (err < 0)
			return err;
	}

	return 0;
}