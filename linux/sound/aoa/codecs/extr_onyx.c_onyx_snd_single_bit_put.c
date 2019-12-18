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
struct TYPE_3__ {int /*<<< orphan*/ * value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct onyx {int /*<<< orphan*/  mutex; scalar_t__ spdif_locked; } ;

/* Variables and functions */
 int EBUSY ; 
 long FLAG_POLARITY_INVERT ; 
 long FLAG_SPDIFLOCK ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  onyx_read_register (struct onyx*,int,int*) ; 
 int onyx_write_register (struct onyx*,int,int) ; 
 struct onyx* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int onyx_snd_single_bit_put(struct snd_kcontrol *kcontrol,
	struct snd_ctl_elem_value *ucontrol)
{
	struct onyx *onyx = snd_kcontrol_chip(kcontrol);
	u8 v = 0, c = 0;
	int err;
	long int pv = kcontrol->private_value;
	u8 polarity = (pv >> 16) & FLAG_POLARITY_INVERT;
	u8 spdiflock = (pv >> 16) & FLAG_SPDIFLOCK;
	u8 address = (pv >> 8) & 0xff;
	u8 mask = pv & 0xff;

	mutex_lock(&onyx->mutex);
	if (spdiflock && onyx->spdif_locked) {
		/* even if alsamixer doesn't care.. */
		err = -EBUSY;
		goto out_unlock;
	}
	onyx_read_register(onyx, address, &v);
	c = v;
	c &= ~(mask);
	if (!!ucontrol->value.integer.value[0] ^ polarity)
		c |= mask;
	err = onyx_write_register(onyx, address, c);

 out_unlock:
	mutex_unlock(&onyx->mutex);

	return !err ? (v != c) : err;
}