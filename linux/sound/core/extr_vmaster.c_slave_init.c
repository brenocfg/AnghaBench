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
struct TYPE_6__ {int /*<<< orphan*/  max; int /*<<< orphan*/  min; } ;
struct TYPE_7__ {TYPE_2__ integer; } ;
struct snd_ctl_elem_info {int count; TYPE_3__ value; int /*<<< orphan*/  type; int /*<<< orphan*/  id; } ;
struct TYPE_5__ {int count; int /*<<< orphan*/  max_val; int /*<<< orphan*/  min_val; int /*<<< orphan*/  type; } ;
struct TYPE_8__ {int (* info ) (TYPE_4__*,struct snd_ctl_elem_info*) ;int /*<<< orphan*/  id; } ;
struct link_slave {int flags; TYPE_1__ info; TYPE_4__ slave; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SNDRV_CTL_ELEM_TYPE_BOOLEAN ; 
 int /*<<< orphan*/  SNDRV_CTL_ELEM_TYPE_INTEGER ; 
 int SND_CTL_SLAVE_NEED_UPDATE ; 
 int /*<<< orphan*/  kfree (struct snd_ctl_elem_info*) ; 
 struct snd_ctl_elem_info* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int slave_update (struct link_slave*) ; 
 int stub1 (TYPE_4__*,struct snd_ctl_elem_info*) ; 

__attribute__((used)) static int slave_init(struct link_slave *slave)
{
	struct snd_ctl_elem_info *uinfo;
	int err;

	if (slave->info.count) {
		/* already initialized */
		if (slave->flags & SND_CTL_SLAVE_NEED_UPDATE)
			return slave_update(slave);
		return 0;
	}

	uinfo = kmalloc(sizeof(*uinfo), GFP_KERNEL);
	if (!uinfo)
		return -ENOMEM;
	uinfo->id = slave->slave.id;
	err = slave->slave.info(&slave->slave, uinfo);
	if (err < 0) {
		kfree(uinfo);
		return err;
	}
	slave->info.type = uinfo->type;
	slave->info.count = uinfo->count;
	if (slave->info.count > 2  ||
	    (slave->info.type != SNDRV_CTL_ELEM_TYPE_INTEGER &&
	     slave->info.type != SNDRV_CTL_ELEM_TYPE_BOOLEAN)) {
		pr_err("ALSA: vmaster: invalid slave element\n");
		kfree(uinfo);
		return -EINVAL;
	}
	slave->info.min_val = uinfo->value.integer.min;
	slave->info.max_val = uinfo->value.integer.max;
	kfree(uinfo);

	return slave_update(slave);
}