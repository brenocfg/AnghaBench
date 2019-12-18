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
struct hda_verb {int dummy; } ;
struct hda_codec {struct ca0132_spec* spec; } ;
struct ca0132_spec {TYPE_1__* spec_init_verbs; int /*<<< orphan*/  desktop_init_verbs; int /*<<< orphan*/  chip_init_verbs; } ;
struct TYPE_2__ {int nid; int param; int verb; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NUM_SPEC_VERBS ; 
 int /*<<< orphan*/  ca0132_init_verbs0 ; 
 int /*<<< orphan*/  ca0132_init_verbs1 ; 
 scalar_t__ ca0132_use_pci_mmio (struct ca0132_spec*) ; 
 TYPE_1__* kcalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ca0132_prepare_verbs(struct hda_codec *codec)
{
/* Verbs + terminator (an empty element) */
#define NUM_SPEC_VERBS 2
	struct ca0132_spec *spec = codec->spec;

	spec->chip_init_verbs = ca0132_init_verbs0;
	/*
	 * Since desktop cards use pci_mmio, this can be used to determine
	 * whether or not to use these verbs instead of a separate bool.
	 */
	if (ca0132_use_pci_mmio(spec))
		spec->desktop_init_verbs = ca0132_init_verbs1;
	spec->spec_init_verbs = kcalloc(NUM_SPEC_VERBS,
					sizeof(struct hda_verb),
					GFP_KERNEL);
	if (!spec->spec_init_verbs)
		return -ENOMEM;

	/* config EAPD */
	spec->spec_init_verbs[0].nid = 0x0b;
	spec->spec_init_verbs[0].param = 0x78D;
	spec->spec_init_verbs[0].verb = 0x00;

	/* Previously commented configuration */
	/*
	spec->spec_init_verbs[2].nid = 0x0b;
	spec->spec_init_verbs[2].param = AC_VERB_SET_EAPD_BTLENABLE;
	spec->spec_init_verbs[2].verb = 0x02;

	spec->spec_init_verbs[3].nid = 0x10;
	spec->spec_init_verbs[3].param = 0x78D;
	spec->spec_init_verbs[3].verb = 0x02;

	spec->spec_init_verbs[4].nid = 0x10;
	spec->spec_init_verbs[4].param = AC_VERB_SET_EAPD_BTLENABLE;
	spec->spec_init_verbs[4].verb = 0x02;
	*/

	/* Terminator: spec->spec_init_verbs[NUM_SPEC_VERBS-1] */
	return 0;
}