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
struct hso_serial {TYPE_1__* shared_int; } ;
struct hso_device {TYPE_1__* shared_int; } ;
struct TYPE_2__ {scalar_t__ ref_count; int /*<<< orphan*/  shared_int_lock; } ;

/* Variables and functions */
 struct hso_serial* dev2ser (struct hso_serial*) ; 
 int /*<<< orphan*/  hso_free_shared_int (TYPE_1__*) ; 
 int /*<<< orphan*/  hso_free_tiomget (struct hso_serial*) ; 
 int /*<<< orphan*/  hso_serial_common_free (struct hso_serial*) ; 
 int /*<<< orphan*/  kfree (struct hso_serial*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hso_free_serial_device(struct hso_device *hso_dev)
{
	struct hso_serial *serial = dev2ser(hso_dev);

	if (!serial)
		return;

	hso_serial_common_free(serial);

	if (serial->shared_int) {
		mutex_lock(&serial->shared_int->shared_int_lock);
		if (--serial->shared_int->ref_count == 0)
			hso_free_shared_int(serial->shared_int);
		else
			mutex_unlock(&serial->shared_int->shared_int_lock);
	}
	hso_free_tiomget(serial);
	kfree(serial);
	kfree(hso_dev);
}