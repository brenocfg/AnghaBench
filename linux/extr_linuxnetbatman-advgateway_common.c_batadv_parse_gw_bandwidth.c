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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int batadv_parse_throughput (struct net_device*,char*,char*,int /*<<< orphan*/ *) ; 
 char* strchr (char*,char) ; 

__attribute__((used)) static bool batadv_parse_gw_bandwidth(struct net_device *net_dev, char *buff,
				      u32 *down, u32 *up)
{
	char *slash_ptr;
	bool ret;

	slash_ptr = strchr(buff, '/');
	if (slash_ptr)
		*slash_ptr = 0;

	ret = batadv_parse_throughput(net_dev, buff, "download gateway speed",
				      down);
	if (!ret)
		return false;

	/* we also got some upload info */
	if (slash_ptr) {
		ret = batadv_parse_throughput(net_dev, slash_ptr + 1,
					      "upload gateway speed", up);
		if (!ret)
			return false;
	}

	return true;
}