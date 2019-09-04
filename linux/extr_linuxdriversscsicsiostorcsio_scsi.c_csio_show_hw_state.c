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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct csio_lnode {int dummy; } ;
struct csio_hw {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  class_to_shost (struct device*) ; 
 scalar_t__ csio_is_hw_ready (struct csio_hw*) ; 
 struct csio_hw* csio_lnode_to_hw (struct csio_lnode*) ; 
 struct csio_lnode* shost_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static ssize_t
csio_show_hw_state(struct device *dev,
		   struct device_attribute *attr, char *buf)
{
	struct csio_lnode *ln = shost_priv(class_to_shost(dev));
	struct csio_hw *hw = csio_lnode_to_hw(ln);

	if (csio_is_hw_ready(hw))
		return snprintf(buf, PAGE_SIZE, "ready\n");
	else
		return snprintf(buf, PAGE_SIZE, "not ready\n");
}