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
struct TYPE_3__ {unsigned int* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 int /*<<< orphan*/  AK_GET_ADDR (int /*<<< orphan*/ ) ; 
 unsigned int AK_GET_MASK (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int put_ak_reg (struct snd_kcontrol*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int snd_akm4xxx_volume_put(struct snd_kcontrol *kcontrol,
				  struct snd_ctl_elem_value *ucontrol)
{
	unsigned int mask = AK_GET_MASK(kcontrol->private_value);
	unsigned int val = ucontrol->value.integer.value[0];
	if (val > mask)
		return -EINVAL;
	return put_ak_reg(kcontrol, AK_GET_ADDR(kcontrol->private_value), val);
}