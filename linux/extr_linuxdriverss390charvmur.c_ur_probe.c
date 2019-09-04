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
struct urdev {int class; } ;
struct ccw_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  handler; } ;

/* Variables and functions */
 int DEV_CLASS_UR_I ; 
 int DEV_CLASS_UR_O ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  TRACE (char*,struct ccw_device*) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct urdev*) ; 
 int /*<<< orphan*/  get_ccwdev_lock (struct ccw_device*) ; 
 int get_urd_class (struct urdev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 
 int ur_create_attributes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ur_int_handler ; 
 int /*<<< orphan*/  ur_remove_attributes (int /*<<< orphan*/ *) ; 
 struct urdev* urdev_alloc (struct ccw_device*) ; 
 int /*<<< orphan*/  urdev_put (struct urdev*) ; 
 int /*<<< orphan*/  vmur_mutex ; 

__attribute__((used)) static int ur_probe(struct ccw_device *cdev)
{
	struct urdev *urd;
	int rc;

	TRACE("ur_probe: cdev=%p\n", cdev);

	mutex_lock(&vmur_mutex);
	urd = urdev_alloc(cdev);
	if (!urd) {
		rc = -ENOMEM;
		goto fail_unlock;
	}

	rc = ur_create_attributes(&cdev->dev);
	if (rc) {
		rc = -ENOMEM;
		goto fail_urdev_put;
	}
	cdev->handler = ur_int_handler;

	/* validate virtual unit record device */
	urd->class = get_urd_class(urd);
	if (urd->class < 0) {
		rc = urd->class;
		goto fail_remove_attr;
	}
	if ((urd->class != DEV_CLASS_UR_I) && (urd->class != DEV_CLASS_UR_O)) {
		rc = -EOPNOTSUPP;
		goto fail_remove_attr;
	}
	spin_lock_irq(get_ccwdev_lock(cdev));
	dev_set_drvdata(&cdev->dev, urd);
	spin_unlock_irq(get_ccwdev_lock(cdev));

	mutex_unlock(&vmur_mutex);
	return 0;

fail_remove_attr:
	ur_remove_attributes(&cdev->dev);
fail_urdev_put:
	urdev_put(urd);
fail_unlock:
	mutex_unlock(&vmur_mutex);
	return rc;
}