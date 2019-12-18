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
struct usbmix_name_map {scalar_t__ dB; scalar_t__ name; } ;

/* Variables and functions */

__attribute__((used)) static inline int
check_ignored_ctl(const struct usbmix_name_map *p)
{
	if (!p || p->name || p->dB)
		return 0;
	return 1;
}