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
struct inode {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  batadv_algo_seq_print_text ; 
 int /*<<< orphan*/  batadv_debugfs_deprecated (struct file*,char*) ; 
 int single_open (struct file*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int batadv_algorithms_open(struct inode *inode, struct file *file)
{
	batadv_debugfs_deprecated(file,
				  "Use genl command BATADV_CMD_GET_ROUTING_ALGOS instead\n");
	return single_open(file, batadv_algo_seq_print_text, NULL);
}