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
struct bus_type {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/ * apm; } ;

/* Variables and functions */
 int ERESTARTSYS ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 TYPE_1__ ap_perms ; 
 int /*<<< orphan*/  ap_perms_mutex ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int snprintf (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t apmask_show(struct bus_type *bus, char *buf)
{
	int rc;

	if (mutex_lock_interruptible(&ap_perms_mutex))
		return -ERESTARTSYS;
	rc = snprintf(buf, PAGE_SIZE,
		      "0x%016lx%016lx%016lx%016lx\n",
		      ap_perms.apm[0], ap_perms.apm[1],
		      ap_perms.apm[2], ap_perms.apm[3]);
	mutex_unlock(&ap_perms_mutex);

	return rc;
}