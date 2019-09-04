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
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  target_pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGES2KB (int /*<<< orphan*/ ) ; 
 TYPE_1__ balloon_stats ; 
 int /*<<< orphan*/  sprintf (char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t show_target_kb(struct device *dev, struct device_attribute *attr,
			      char *buf)
{
	return sprintf(buf, "%lu\n", PAGES2KB(balloon_stats.target_pages));
}