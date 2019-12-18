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
typedef  int u8 ;
struct snd_kcontrol {long private_value; } ;
struct TYPE_3__ {int* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct onyx {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 long FLAG_POLARITY_INVERT ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  onyx_read_register (struct onyx*,int,int*) ; 
 struct onyx* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int onyx_snd_single_bit_get(struct snd_kcontrol *kcontrol,
	struct snd_ctl_elem_value *ucontrol)
{
	struct onyx *onyx = snd_kcontrol_chip(kcontrol);
	u8 c;
	long int pv = kcontrol->private_value;
	u8 polarity = (pv >> 16) & FLAG_POLARITY_INVERT;
	u8 address = (pv >> 8) & 0xff;
	u8 mask = pv & 0xff;

	mutex_lock(&onyx->mutex);
	onyx_read_register(onyx, address, &c);
	mutex_unlock(&onyx->mutex);

	ucontrol->value.integer.value[0] = !!(c & mask) ^ polarity;

	return 0;
}