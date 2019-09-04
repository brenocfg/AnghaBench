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
struct snd_kcontrol {int dummy; } ;
struct snd_ice1712 {int /*<<< orphan*/  i2c; struct ews_spec* spec; } ;
struct TYPE_3__ {int* item; } ;
struct TYPE_4__ {TYPE_1__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_2__ value; int /*<<< orphan*/  id; } ;
struct ews_spec {int /*<<< orphan*/ * i2cdevs; } ;

/* Variables and functions */
 int EIO ; 
 size_t EWS_I2C_PCF1 ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int snd_ctl_get_ioffidx (struct snd_kcontrol*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_i2c_lock (int /*<<< orphan*/ ) ; 
 int snd_i2c_readbytes (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  snd_i2c_unlock (int /*<<< orphan*/ ) ; 
 struct snd_ice1712* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int snd_ice1712_ews88mt_input_sense_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
	struct snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	struct ews_spec *spec = ice->spec;
	int channel = snd_ctl_get_ioffidx(kcontrol, &ucontrol->id);
	unsigned char data;

	if (snd_BUG_ON(channel < 0 || channel > 7))
		return 0;
	snd_i2c_lock(ice->i2c);
	if (snd_i2c_readbytes(spec->i2cdevs[EWS_I2C_PCF1], &data, 1) != 1) {
		snd_i2c_unlock(ice->i2c);
		return -EIO;
	}
	/* reversed; high = +4dBu, low = -10dBV */
	ucontrol->value.enumerated.item[0] = data & (1 << channel) ? 0 : 1;
	snd_i2c_unlock(ice->i2c);
	return 0;
}