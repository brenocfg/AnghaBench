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
struct fcoe_fcf_device {int /*<<< orphan*/  state; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  FCOE_FCF_STATE_MAX_NAMELEN ; 
 struct fcoe_fcf_device* dev_to_fcf (struct device*) ; 
 char* get_fcoe_fcf_state_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,char const*) ; 

__attribute__((used)) static ssize_t show_fcf_state(struct device *dev,
			      struct device_attribute *attr,
			      char *buf)
{
	struct fcoe_fcf_device *fcf = dev_to_fcf(dev);
	const char *name;
	name = get_fcoe_fcf_state_name(fcf->state);
	if (!name)
		return -EINVAL;
	return snprintf(buf, FCOE_FCF_STATE_MAX_NAMELEN, "%s\n", name);
}