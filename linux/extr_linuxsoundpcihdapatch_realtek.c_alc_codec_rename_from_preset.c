#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ vendor_id; } ;
struct hda_codec {TYPE_3__* bus; TYPE_1__ core; } ;
struct alc_codec_rename_table {scalar_t__ vendor_id; int coef_mask; int coef_bits; int /*<<< orphan*/  name; } ;
struct alc_codec_rename_pci_table {scalar_t__ codec_vendor_id; scalar_t__ pci_subvendor; scalar_t__ pci_subdevice; int /*<<< orphan*/  name; } ;
struct TYPE_6__ {TYPE_2__* pci; } ;
struct TYPE_5__ {scalar_t__ subsystem_vendor; scalar_t__ subsystem_device; } ;

/* Variables and functions */
 int alc_codec_rename (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int alc_get_coef0 (struct hda_codec*) ; 
 struct alc_codec_rename_pci_table* rename_pci_tbl ; 
 struct alc_codec_rename_table* rename_tbl ; 

__attribute__((used)) static int alc_codec_rename_from_preset(struct hda_codec *codec)
{
	const struct alc_codec_rename_table *p;
	const struct alc_codec_rename_pci_table *q;

	for (p = rename_tbl; p->vendor_id; p++) {
		if (p->vendor_id != codec->core.vendor_id)
			continue;
		if ((alc_get_coef0(codec) & p->coef_mask) == p->coef_bits)
			return alc_codec_rename(codec, p->name);
	}

	if (!codec->bus->pci)
		return 0;
	for (q = rename_pci_tbl; q->codec_vendor_id; q++) {
		if (q->codec_vendor_id != codec->core.vendor_id)
			continue;
		if (q->pci_subvendor != codec->bus->pci->subsystem_vendor)
			continue;
		if (!q->pci_subdevice ||
		    q->pci_subdevice == codec->bus->pci->subsystem_device)
			return alc_codec_rename(codec, q->name);
	}

	return 0;
}