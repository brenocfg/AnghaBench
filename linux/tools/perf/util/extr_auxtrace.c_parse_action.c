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
struct addr_filter {int action; int start; int range; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  strcmp (int,char*) ; 

__attribute__((used)) static int parse_action(struct addr_filter *filt)
{
	if (!strcmp(filt->action, "filter")) {
		filt->start = true;
		filt->range = true;
	} else if (!strcmp(filt->action, "start")) {
		filt->start = true;
	} else if (!strcmp(filt->action, "stop")) {
		filt->start = false;
	} else if (!strcmp(filt->action, "tracestop")) {
		filt->start = false;
		filt->range = true;
		filt->action += 5; /* Change 'tracestop' to 'stop' */
	} else {
		return -EINVAL;
	}
	return 0;
}