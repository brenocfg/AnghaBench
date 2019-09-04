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
struct snd_kcontrol {int /*<<< orphan*/  private_value; } ;
struct snd_i2c_device {int /*<<< orphan*/  bus; } ;
struct TYPE_3__ {int* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 int snd_cs8427_reg_read (struct snd_i2c_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_i2c_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_i2c_unlock (int /*<<< orphan*/ ) ; 
 struct snd_i2c_device* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int snd_cs8427_in_status_get(struct snd_kcontrol *kcontrol,
				    struct snd_ctl_elem_value *ucontrol)
{
	struct snd_i2c_device *device = snd_kcontrol_chip(kcontrol);
	int data;

	snd_i2c_lock(device->bus);
	data = snd_cs8427_reg_read(device, kcontrol->private_value);
	snd_i2c_unlock(device->bus);
	if (data < 0)
		return data;
	ucontrol->value.integer.value[0] = data;
	return 0;
}