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
struct net_device {int dummy; } ;
struct attribute {int /*<<< orphan*/  name; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  atomic_t ;

/* Variables and functions */
 int batadv_store_uint_attr (char const*,size_t,struct net_device*,struct net_device*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t __batadv_store_uint_attr(const char *buff, size_t count,
					int min, int max,
					void (*post_func)(struct net_device *),
					const struct attribute *attr,
					atomic_t *attr_store,
					struct net_device *net_dev,
					struct net_device *slave_dev)
{
	int ret;

	ret = batadv_store_uint_attr(buff, count, net_dev, slave_dev,
				     attr->name, min, max, attr_store);
	if (post_func && ret)
		post_func(net_dev);

	return ret;
}