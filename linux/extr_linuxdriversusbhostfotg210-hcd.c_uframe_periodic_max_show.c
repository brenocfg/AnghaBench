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
struct fotg210_hcd {int /*<<< orphan*/  uframe_periodic_max; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  bus_to_hcd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_get_drvdata (struct device*) ; 
 struct fotg210_hcd* hcd_to_fotg210 (int /*<<< orphan*/ ) ; 
 int scnprintf (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t uframe_periodic_max_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct fotg210_hcd *fotg210;
	int n;

	fotg210 = hcd_to_fotg210(bus_to_hcd(dev_get_drvdata(dev)));
	n = scnprintf(buf, PAGE_SIZE, "%d\n", fotg210->uframe_periodic_max);
	return n;
}