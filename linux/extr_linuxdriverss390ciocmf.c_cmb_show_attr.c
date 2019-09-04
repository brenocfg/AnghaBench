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
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  enum cmb_index { ____Placeholder_cmb_index } cmb_index ;

/* Variables and functions */
 scalar_t__ cmf_read (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned long long) ; 
 int /*<<< orphan*/  to_ccwdev (struct device*) ; 

__attribute__((used)) static ssize_t cmb_show_attr(struct device *dev, char *buf, enum cmb_index idx)
{
	return sprintf(buf, "%lld\n",
		(unsigned long long) cmf_read(to_ccwdev(dev), idx));
}