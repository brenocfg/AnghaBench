#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned long expires; } ;
struct idletimer_tg {TYPE_2__ timer; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
struct device_attribute {TYPE_1__ attr; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct idletimer_tg* __idletimer_tg_find_by_label (int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int jiffies_to_msecs (scalar_t__) ; 
 int /*<<< orphan*/  list_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 scalar_t__ time_after (unsigned long,scalar_t__) ; 

__attribute__((used)) static ssize_t idletimer_tg_show(struct device *dev,
				 struct device_attribute *attr, char *buf)
{
	struct idletimer_tg *timer;
	unsigned long expires = 0;

	mutex_lock(&list_mutex);

	timer =	__idletimer_tg_find_by_label(attr->attr.name);
	if (timer)
		expires = timer->timer.expires;

	mutex_unlock(&list_mutex);

	if (time_after(expires, jiffies))
		return sprintf(buf, "%u\n",
			       jiffies_to_msecs(expires - jiffies) / 1000);

	return sprintf(buf, "0\n");
}