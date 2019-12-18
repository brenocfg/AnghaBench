#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct snd_kcontrol {int dummy; } ;
struct link_master {int /*<<< orphan*/  val; int /*<<< orphan*/  hook_private_data; int /*<<< orphan*/  (* hook ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int master_init (struct link_master*) ; 
 struct link_master* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sync_slaves (struct link_master*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void snd_ctl_sync_vmaster(struct snd_kcontrol *kcontrol, bool hook_only)
{
	struct link_master *master;
	bool first_init = false;

	if (!kcontrol)
		return;
	master = snd_kcontrol_chip(kcontrol);
	if (!hook_only) {
		int err = master_init(master);
		if (err < 0)
			return;
		first_init = err;
		err = sync_slaves(master, master->val, master->val);
		if (err < 0)
			return;
	}

	if (master->hook && !first_init)
		master->hook(master->hook_private_data, master->val);
}