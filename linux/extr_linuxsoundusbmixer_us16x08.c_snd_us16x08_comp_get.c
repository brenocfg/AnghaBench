#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  id; } ;
struct usb_mixer_elem_info {TYPE_3__ head; struct snd_us16x08_comp_store* private_data; } ;
struct snd_us16x08_comp_store {int /*<<< orphan*/ ** val; } ;
struct snd_kcontrol {struct usb_mixer_elem_info* private_data; } ;
struct TYPE_8__ {int /*<<< orphan*/ * value; } ;
struct TYPE_5__ {TYPE_4__ integer; } ;
struct TYPE_6__ {int index; } ;
struct snd_ctl_elem_value {TYPE_1__ value; TYPE_2__ id; } ;

/* Variables and functions */
 int COMP_STORE_IDX (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_us16x08_comp_get(struct snd_kcontrol *kcontrol,
	struct snd_ctl_elem_value *ucontrol)
{
	struct usb_mixer_elem_info *elem = kcontrol->private_data;
	struct snd_us16x08_comp_store *store = elem->private_data;
	int index = ucontrol->id.index;
	int val_idx = COMP_STORE_IDX(elem->head.id);

	ucontrol->value.integer.value[0] = store->val[val_idx][index];

	return 0;
}