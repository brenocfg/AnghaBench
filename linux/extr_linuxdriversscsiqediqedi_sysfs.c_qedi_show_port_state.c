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
struct qedi_ctx {int /*<<< orphan*/  link_state; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 scalar_t__ QEDI_LINK_UP ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 struct qedi_ctx* qedi_dev_to_hba (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*) ; 

__attribute__((used)) static ssize_t qedi_show_port_state(struct device *dev,
				    struct device_attribute *attr,
				    char *buf)
{
	struct qedi_ctx *qedi = qedi_dev_to_hba(dev);

	if (atomic_read(&qedi->link_state) == QEDI_LINK_UP)
		return sprintf(buf, "Online\n");
	else
		return sprintf(buf, "Linkdown\n");
}