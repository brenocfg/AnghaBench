#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct xt_tgchk_param {struct xt_led_info* targinfo; } ;
struct TYPE_2__ {struct xt_led_info_internal* name; } ;
struct xt_led_info_internal {int refcnt; struct xt_led_info_internal* trigger_id; int /*<<< orphan*/  list; int /*<<< orphan*/  timer; TYPE_1__ netfilter_led_trigger; } ;
struct xt_led_info {char* id; struct xt_led_info_internal* internal_data; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct xt_led_info_internal*) ; 
 struct xt_led_info_internal* kstrdup (char*,int /*<<< orphan*/ ) ; 
 struct xt_led_info_internal* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  led_timeout_callback ; 
 struct xt_led_info_internal* led_trigger_lookup (char*) ; 
 int led_trigger_register (TYPE_1__*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info_ratelimited (char*) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xt_led_mutex ; 
 int /*<<< orphan*/  xt_led_triggers ; 

__attribute__((used)) static int led_tg_check(const struct xt_tgchk_param *par)
{
	struct xt_led_info *ledinfo = par->targinfo;
	struct xt_led_info_internal *ledinternal;
	int err;

	if (ledinfo->id[0] == '\0')
		return -EINVAL;

	mutex_lock(&xt_led_mutex);

	ledinternal = led_trigger_lookup(ledinfo->id);
	if (ledinternal) {
		ledinternal->refcnt++;
		goto out;
	}

	err = -ENOMEM;
	ledinternal = kzalloc(sizeof(struct xt_led_info_internal), GFP_KERNEL);
	if (!ledinternal)
		goto exit_mutex_only;

	ledinternal->trigger_id = kstrdup(ledinfo->id, GFP_KERNEL);
	if (!ledinternal->trigger_id)
		goto exit_internal_alloc;

	ledinternal->refcnt = 1;
	ledinternal->netfilter_led_trigger.name = ledinternal->trigger_id;

	err = led_trigger_register(&ledinternal->netfilter_led_trigger);
	if (err) {
		pr_info_ratelimited("Trigger name is already in use.\n");
		goto exit_alloc;
	}

	/* Since the letinternal timer can be shared between multiple targets,
	 * always set it up, even if the current target does not need it
	 */
	timer_setup(&ledinternal->timer, led_timeout_callback, 0);

	list_add_tail(&ledinternal->list, &xt_led_triggers);

out:
	mutex_unlock(&xt_led_mutex);

	ledinfo->internal_data = ledinternal;

	return 0;

exit_alloc:
	kfree(ledinternal->trigger_id);

exit_internal_alloc:
	kfree(ledinternal);

exit_mutex_only:
	mutex_unlock(&xt_led_mutex);

	return err;
}