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
struct iwinfo_ops {int dummy; } ;

/* Variables and functions */
 struct iwinfo_ops* iwinfo_backend (char const*) ; 

int open_backend(const struct iwinfo_ops **iw, const char *ifname)
{
	*iw = iwinfo_backend(ifname);

	if (!(*iw))
		return 1;

	return 0;
}