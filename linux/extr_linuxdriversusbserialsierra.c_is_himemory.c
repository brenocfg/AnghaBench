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
typedef  scalar_t__ u8 ;
struct sierra_iface_info {scalar_t__* ifaceinfo; int infolen; } ;

/* Variables and functions */

__attribute__((used)) static int is_himemory(const u8 ifnum,
				const struct sierra_iface_info *himemorylist)
{
	const u8  *info;
	int i;

	if (himemorylist) {
		info = himemorylist->ifaceinfo;

		for (i=0; i < himemorylist->infolen; i++) {
			if (info[i] == ifnum)
				return 1;
		}
	}
	return 0;
}