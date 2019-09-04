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
struct tun_struct {int /*<<< orphan*/  owner; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  current_user_ns () ; 
 int from_kuid_munged (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tun_struct* netdev_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 int /*<<< orphan*/  to_net_dev (struct device*) ; 
 scalar_t__ uid_valid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t tun_show_owner(struct device *dev, struct device_attribute *attr,
			      char *buf)
{
	struct tun_struct *tun = netdev_priv(to_net_dev(dev));
	return uid_valid(tun->owner)?
		sprintf(buf, "%u\n",
			from_kuid_munged(current_user_ns(), tun->owner)):
		sprintf(buf, "-1\n");
}