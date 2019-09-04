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
struct var_t {scalar_t__ var_id; } ;
struct TYPE_7__ {scalar_t__ name; } ;
struct spk_synth {scalar_t__ checkval; scalar_t__ (* probe ) (struct spk_synth*) ;int /*<<< orphan*/  flags; TYPE_3__ attributes; int /*<<< orphan*/  long_name; struct var_t* vars; int /*<<< orphan*/  init; int /*<<< orphan*/  full; int /*<<< orphan*/  jiffies; int /*<<< orphan*/  trigger; int /*<<< orphan*/  delay; int /*<<< orphan*/  name; scalar_t__ alive; } ;
struct TYPE_5__ {int /*<<< orphan*/  default_val; int /*<<< orphan*/  value; } ;
struct TYPE_6__ {TYPE_1__ n; } ;
struct TYPE_8__ {TYPE_2__ u; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 scalar_t__ MAXVARS ; 
 scalar_t__ SYNTH_CHECK ; 
 int /*<<< orphan*/  pr_warn (char*,...) ; 
 int /*<<< orphan*/  speakup_event ; 
 int /*<<< orphan*/  speakup_kobj ; 
 int /*<<< orphan*/  speakup_register_var (struct var_t*) ; 
 scalar_t__ speakup_task ; 
 int /*<<< orphan*/  spk_quiet_boot ; 
 scalar_t__ stub1 (struct spk_synth*) ; 
 struct spk_synth* synth ; 
 int /*<<< orphan*/  synth_flags ; 
 int /*<<< orphan*/  synth_printf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  synth_release () ; 
 TYPE_4__* synth_time_vars ; 
 scalar_t__ sysfs_create_group (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  wake_up_interruptible_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_process (scalar_t__) ; 

__attribute__((used)) static int do_synth_init(struct spk_synth *in_synth)
{
	struct var_t *var;

	synth_release();
	if (in_synth->checkval != SYNTH_CHECK)
		return -EINVAL;
	synth = in_synth;
	synth->alive = 0;
	pr_warn("synth probe\n");
	if (synth->probe(synth) < 0) {
		pr_warn("%s: device probe failed\n", in_synth->name);
		synth = NULL;
		return -ENODEV;
	}
	synth_time_vars[0].u.n.value =
		synth_time_vars[0].u.n.default_val = synth->delay;
	synth_time_vars[1].u.n.value =
		synth_time_vars[1].u.n.default_val = synth->trigger;
	synth_time_vars[2].u.n.value =
		synth_time_vars[2].u.n.default_val = synth->jiffies;
	synth_time_vars[3].u.n.value =
		synth_time_vars[3].u.n.default_val = synth->full;
	synth_printf("%s", synth->init);
	for (var = synth->vars;
		(var->var_id >= 0) && (var->var_id < MAXVARS); var++)
		speakup_register_var(var);
	if (!spk_quiet_boot)
		synth_printf("%s found\n", synth->long_name);
	if (synth->attributes.name &&
	    sysfs_create_group(speakup_kobj, &synth->attributes) < 0)
		return -ENOMEM;
	synth_flags = synth->flags;
	wake_up_interruptible_all(&speakup_event);
	if (speakup_task)
		wake_up_process(speakup_task);
	return 0;
}