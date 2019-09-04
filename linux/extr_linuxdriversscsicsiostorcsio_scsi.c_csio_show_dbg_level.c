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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int log_level; } ;
struct csio_lnode {TYPE_1__ params; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  class_to_shost (struct device*) ; 
 struct csio_lnode* shost_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static ssize_t
csio_show_dbg_level(struct device *dev,
		   struct device_attribute *attr, char *buf)
{
	struct csio_lnode *ln = shost_priv(class_to_shost(dev));

	return snprintf(buf, PAGE_SIZE, "%x\n", ln->params.log_level);
}