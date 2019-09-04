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
struct typec_port {TYPE_1__* cap; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
typedef  enum typec_role { ____Placeholder_typec_role } typec_role ;
struct TYPE_2__ {int (* vconn_set ) (TYPE_1__*,int) ;int /*<<< orphan*/  pd_revision; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int kstrtobool (char const*,int*) ; 
 int stub1 (TYPE_1__*,int) ; 
 struct typec_port* to_typec_port (struct device*) ; 

__attribute__((used)) static ssize_t vconn_source_store(struct device *dev,
				  struct device_attribute *attr,
				  const char *buf, size_t size)
{
	struct typec_port *port = to_typec_port(dev);
	bool source;
	int ret;

	if (!port->cap->pd_revision) {
		dev_dbg(dev, "VCONN swap depends on USB Power Delivery\n");
		return -EOPNOTSUPP;
	}

	if (!port->cap->vconn_set) {
		dev_dbg(dev, "VCONN swapping not supported\n");
		return -EOPNOTSUPP;
	}

	ret = kstrtobool(buf, &source);
	if (ret)
		return ret;

	ret = port->cap->vconn_set(port->cap, (enum typec_role)source);
	if (ret)
		return ret;

	return size;
}