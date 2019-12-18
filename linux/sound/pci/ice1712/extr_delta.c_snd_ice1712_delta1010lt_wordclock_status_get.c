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
struct snd_kcontrol {int dummy; } ;
struct snd_ice1712 {int /*<<< orphan*/  cs8427; TYPE_3__* card; } ;
struct TYPE_4__ {int* value; } ;
struct TYPE_5__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 char CS8427_UNLOCK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,char) ; 
 int /*<<< orphan*/  snd_i2c_readbytes (int /*<<< orphan*/ ,char*,int) ; 
 int snd_i2c_sendbytes (int /*<<< orphan*/ ,char*,int) ; 
 struct snd_ice1712* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int snd_ice1712_delta1010lt_wordclock_status_get(struct snd_kcontrol *kcontrol,
			 struct snd_ctl_elem_value *ucontrol)
{
	char reg = 0x10; /* CS8427 receiver error register */
	struct snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);

	if (snd_i2c_sendbytes(ice->cs8427, &reg, 1) != 1)
		dev_err(ice->card->dev,
			"unable to send register 0x%x byte to CS8427\n", reg);
	snd_i2c_readbytes(ice->cs8427, &reg, 1);
	ucontrol->value.integer.value[0] = (reg & CS8427_UNLOCK) ? 1 : 0;
	return 0;
}