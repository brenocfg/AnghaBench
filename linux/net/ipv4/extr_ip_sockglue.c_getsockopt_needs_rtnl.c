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

/* Variables and functions */
#define  IP_MSFILTER 129 
#define  MCAST_MSFILTER 128 

__attribute__((used)) static bool getsockopt_needs_rtnl(int optname)
{
	switch (optname) {
	case IP_MSFILTER:
	case MCAST_MSFILTER:
		return true;
	}
	return false;
}