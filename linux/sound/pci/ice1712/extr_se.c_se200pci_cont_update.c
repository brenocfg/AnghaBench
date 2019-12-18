#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_ice1712 {struct se_spec* spec; } ;
struct se_spec {TYPE_1__* vol; } ;
struct TYPE_4__ {int target; int /*<<< orphan*/  ch; } ;
struct TYPE_3__ {int /*<<< orphan*/  ch1; int /*<<< orphan*/  ch2; } ;

/* Variables and functions */
#define  WM8766 133 
#define  WM8776afl 132 
#define  WM8776agc 131 
#define  WM8776in 130 
#define  WM8776out 129 
#define  WM8776sel 128 
 int /*<<< orphan*/  se200pci_WM8766_set_volume (struct snd_ice1712*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  se200pci_WM8776_set_afl (struct snd_ice1712*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  se200pci_WM8776_set_agc (struct snd_ice1712*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  se200pci_WM8776_set_input_selector (struct snd_ice1712*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  se200pci_WM8776_set_input_volume (struct snd_ice1712*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  se200pci_WM8776_set_output_volume (struct snd_ice1712*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* se200pci_cont ; 

__attribute__((used)) static void se200pci_cont_update(struct snd_ice1712 *ice, int n)
{
	struct se_spec *spec = ice->spec;
	switch (se200pci_cont[n].target) {
	case WM8766:
		se200pci_WM8766_set_volume(ice,
					   se200pci_cont[n].ch,
					   spec->vol[n].ch1,
					   spec->vol[n].ch2);
		break;

	case WM8776in:
		se200pci_WM8776_set_input_volume(ice,
						 spec->vol[n].ch1,
						 spec->vol[n].ch2);
		break;

	case WM8776out:
		se200pci_WM8776_set_output_volume(ice,
						  spec->vol[n].ch1,
						  spec->vol[n].ch2);
		break;

	case WM8776sel:
		se200pci_WM8776_set_input_selector(ice,
						   spec->vol[n].ch1);
		break;

	case WM8776agc:
		se200pci_WM8776_set_agc(ice, spec->vol[n].ch1);
		break;

	case WM8776afl:
		se200pci_WM8776_set_afl(ice, spec->vol[n].ch1);
		break;

	default:
		break;
	}
}