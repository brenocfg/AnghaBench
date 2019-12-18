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
struct inode {scalar_t__ i_private; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  batadv_debugfs_deprecated (struct file*,char*) ; 
 int /*<<< orphan*/  batadv_orig_seq_print_text ; 
 int single_open (struct file*,int /*<<< orphan*/ ,struct net_device*) ; 

__attribute__((used)) static int batadv_originators_open(struct inode *inode, struct file *file)
{
	struct net_device *net_dev = (struct net_device *)inode->i_private;

	batadv_debugfs_deprecated(file,
				  "Use genl command BATADV_CMD_GET_ORIGINATORS instead\n");
	return single_open(file, batadv_orig_seq_print_text, net_dev);
}