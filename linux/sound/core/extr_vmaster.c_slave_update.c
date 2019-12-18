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
struct TYPE_6__ {int /*<<< orphan*/ * value; } ;
struct TYPE_7__ {TYPE_2__ integer; } ;
struct snd_ctl_elem_value {TYPE_3__ value; int /*<<< orphan*/  id; } ;
struct TYPE_5__ {int count; } ;
struct TYPE_8__ {int (* get ) (TYPE_4__*,struct snd_ctl_elem_value*) ;int /*<<< orphan*/  id; } ;
struct link_slave {int /*<<< orphan*/ * vals; TYPE_1__ info; TYPE_4__ slave; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct snd_ctl_elem_value*) ; 
 struct snd_ctl_elem_value* kzalloc (int,int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_4__*,struct snd_ctl_elem_value*) ; 

__attribute__((used)) static int slave_update(struct link_slave *slave)
{
	struct snd_ctl_elem_value *uctl;
	int err, ch;

	uctl = kzalloc(sizeof(*uctl), GFP_KERNEL);
	if (!uctl)
		return -ENOMEM;
	uctl->id = slave->slave.id;
	err = slave->slave.get(&slave->slave, uctl);
	if (err < 0)
		goto error;
	for (ch = 0; ch < slave->info.count; ch++)
		slave->vals[ch] = uctl->value.integer.value[ch];
 error:
	kfree(uctl);
	return err < 0 ? err : 0;
}