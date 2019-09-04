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
struct TYPE_5__ {int /*<<< orphan*/ * value; } ;
struct TYPE_6__ {TYPE_2__ integer; } ;
struct snd_ctl_elem_value {TYPE_3__ value; } ;
struct TYPE_4__ {int count; } ;
struct link_slave {int /*<<< orphan*/ * vals; TYPE_1__ info; } ;

/* Variables and functions */
 int slave_init (struct link_slave*) ; 

__attribute__((used)) static int slave_get_val(struct link_slave *slave,
			 struct snd_ctl_elem_value *ucontrol)
{
	int err, ch;

	err = slave_init(slave);
	if (err < 0)
		return err;
	for (ch = 0; ch < slave->info.count; ch++)
		ucontrol->value.integer.value[ch] = slave->vals[ch];
	return 0;
}