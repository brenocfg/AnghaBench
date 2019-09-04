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
struct net_bridge_port {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOENT ; 
 struct net_device* __dev_get_by_name (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_net (int /*<<< orphan*/ ) ; 
 int nbp_backup_change (struct net_bridge_port*,struct net_device*) ; 
 char* strchr (char*,char) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static int store_backup_port(struct net_bridge_port *p, char *buf)
{
	struct net_device *backup_dev = NULL;
	char *nl = strchr(buf, '\n');

	if (nl)
		*nl = '\0';

	if (strlen(buf) > 0) {
		backup_dev = __dev_get_by_name(dev_net(p->dev), buf);
		if (!backup_dev)
			return -ENOENT;
	}

	return nbp_backup_change(p, backup_dev);
}