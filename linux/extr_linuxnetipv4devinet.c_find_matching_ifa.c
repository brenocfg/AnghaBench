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
struct in_ifaddr {scalar_t__ ifa_local; scalar_t__ ifa_mask; int /*<<< orphan*/  ifa_address; struct in_ifaddr* ifa_next; struct in_device* ifa_dev; } ;
struct in_device {struct in_ifaddr* ifa_list; } ;

/* Variables and functions */
 scalar_t__ inet_ifa_match (int /*<<< orphan*/ ,struct in_ifaddr*) ; 

__attribute__((used)) static struct in_ifaddr *find_matching_ifa(struct in_ifaddr *ifa)
{
	struct in_device *in_dev = ifa->ifa_dev;
	struct in_ifaddr *ifa1, **ifap;

	if (!ifa->ifa_local)
		return NULL;

	for (ifap = &in_dev->ifa_list; (ifa1 = *ifap) != NULL;
	     ifap = &ifa1->ifa_next) {
		if (ifa1->ifa_mask == ifa->ifa_mask &&
		    inet_ifa_match(ifa1->ifa_address, ifa) &&
		    ifa1->ifa_local == ifa->ifa_local)
			return ifa1;
	}
	return NULL;
}