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
typedef  int u32 ;

/* Variables and functions */
 int CEPH_OSD_EXISTS ; 
 int CEPH_OSD_UP ; 
 int /*<<< orphan*/  snprintf (char*,int,char*) ; 

char *ceph_osdmap_state_str(char *str, int len, u32 state)
{
	if (!len)
		return str;

	if ((state & CEPH_OSD_EXISTS) && (state & CEPH_OSD_UP))
		snprintf(str, len, "exists, up");
	else if (state & CEPH_OSD_EXISTS)
		snprintf(str, len, "exists");
	else if (state & CEPH_OSD_UP)
		snprintf(str, len, "up");
	else
		snprintf(str, len, "doesn't exist");

	return str;
}