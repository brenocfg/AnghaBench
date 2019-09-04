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
typedef  int u8 ;
struct TYPE_3__ {int /*<<< orphan*/  conf; } ;
struct dp_altmode {int /*<<< orphan*/  lock; TYPE_2__* alt; TYPE_1__ data; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_4__ {int /*<<< orphan*/  vdo; } ;

/* Variables and functions */
 int DP_CAP_DFP_D_PIN_ASSIGN (int /*<<< orphan*/ ) ; 
 int DP_CAP_UFP_D_PIN_ASSIGN (int /*<<< orphan*/ ) ; 
 scalar_t__ DP_CONF_CURRENTLY (int /*<<< orphan*/ ) ; 
 scalar_t__ DP_CONF_DFP_D ; 
 int /*<<< orphan*/  DP_CONF_GET_PIN_ASSIGN (int /*<<< orphan*/ ) ; 
 struct dp_altmode* dev_get_drvdata (struct device*) ; 
 int get_count_order (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 char** pin_assignments ; 
 scalar_t__ sprintf (char*,char*,char*) ; 

__attribute__((used)) static ssize_t pin_assignment_show(struct device *dev,
				   struct device_attribute *attr, char *buf)
{
	struct dp_altmode *dp = dev_get_drvdata(dev);
	u8 assignments;
	int len = 0;
	u8 cur;
	int i;

	mutex_lock(&dp->lock);

	cur = get_count_order(DP_CONF_GET_PIN_ASSIGN(dp->data.conf));

	if (DP_CONF_CURRENTLY(dp->data.conf) == DP_CONF_DFP_D)
		assignments = DP_CAP_UFP_D_PIN_ASSIGN(dp->alt->vdo);
	else
		assignments = DP_CAP_DFP_D_PIN_ASSIGN(dp->alt->vdo);

	for (i = 0; assignments; assignments >>= 1, i++) {
		if (assignments & 1) {
			if (i == cur)
				len += sprintf(buf + len, "[%s] ",
					       pin_assignments[i]);
			else
				len += sprintf(buf + len, "%s ",
					       pin_assignments[i]);
		}
	}

	mutex_unlock(&dp->lock);

	buf[len - 1] = '\n';
	return len;
}