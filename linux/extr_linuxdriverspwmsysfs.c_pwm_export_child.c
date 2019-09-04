#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  groups; int /*<<< orphan*/  devt; struct device* parent; int /*<<< orphan*/  release; } ;
struct pwm_export {TYPE_1__ child; int /*<<< orphan*/  lock; struct pwm_device* pwm; } ;
struct pwm_device {int /*<<< orphan*/  hwpwm; int /*<<< orphan*/  flags; } ;
struct device {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KOBJ_CHANGE ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PWMF_EXPORTED ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_name (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int device_register (TYPE_1__*) ; 
 char* kasprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int /*<<< orphan*/  kobject_uevent_env (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**) ; 
 struct pwm_export* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (TYPE_1__*) ; 
 int /*<<< orphan*/  pwm_export_release ; 
 int /*<<< orphan*/  pwm_groups ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pwm_export_child(struct device *parent, struct pwm_device *pwm)
{
	struct pwm_export *export;
	char *pwm_prop[2];
	int ret;

	if (test_and_set_bit(PWMF_EXPORTED, &pwm->flags))
		return -EBUSY;

	export = kzalloc(sizeof(*export), GFP_KERNEL);
	if (!export) {
		clear_bit(PWMF_EXPORTED, &pwm->flags);
		return -ENOMEM;
	}

	export->pwm = pwm;
	mutex_init(&export->lock);

	export->child.release = pwm_export_release;
	export->child.parent = parent;
	export->child.devt = MKDEV(0, 0);
	export->child.groups = pwm_groups;
	dev_set_name(&export->child, "pwm%u", pwm->hwpwm);

	ret = device_register(&export->child);
	if (ret) {
		clear_bit(PWMF_EXPORTED, &pwm->flags);
		put_device(&export->child);
		export = NULL;
		return ret;
	}
	pwm_prop[0] = kasprintf(GFP_KERNEL, "EXPORT=pwm%u", pwm->hwpwm);
	pwm_prop[1] = NULL;
	kobject_uevent_env(&parent->kobj, KOBJ_CHANGE, pwm_prop);
	kfree(pwm_prop[0]);

	return 0;
}