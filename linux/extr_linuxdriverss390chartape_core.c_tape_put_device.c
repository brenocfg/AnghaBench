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
struct tape_device {struct tape_device* modeset_byte; int /*<<< orphan*/  ref_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DBF_EVENT (int,char*,struct tape_device*,int) ; 
 int atomic_dec_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct tape_device*) ; 

void
tape_put_device(struct tape_device *device)
{
	int count;

	count = atomic_dec_return(&device->ref_count);
	DBF_EVENT(4, "tape_put_device(%p) -> %i\n", device, count);
	BUG_ON(count < 0);
	if (count == 0) {
		kfree(device->modeset_byte);
		kfree(device);
	}
}