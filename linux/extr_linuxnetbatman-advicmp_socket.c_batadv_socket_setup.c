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
struct dentry {int dummy; } ;
struct batadv_priv {int /*<<< orphan*/  debug_dir; } ;

/* Variables and functions */
 int /*<<< orphan*/  BATADV_ICMP_SOCKET ; 
 int ENOMEM ; 
 int /*<<< orphan*/  batadv_fops ; 
 struct dentry* debugfs_create_file (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct batadv_priv*,int /*<<< orphan*/ *) ; 

int batadv_socket_setup(struct batadv_priv *bat_priv)
{
	struct dentry *d;

	if (!bat_priv->debug_dir)
		goto err;

	d = debugfs_create_file(BATADV_ICMP_SOCKET, 0600, bat_priv->debug_dir,
				bat_priv, &batadv_fops);
	if (!d)
		goto err;

	return 0;

err:
	return -ENOMEM;
}