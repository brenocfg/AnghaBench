#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct file_operations {int dummy; } ;
struct dwc3_ep {int dummy; } ;
struct dentry {int dummy; } ;
struct TYPE_3__ {char* name; struct file_operations* fops; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  S_IRUGO ; 
 int /*<<< orphan*/  debugfs_create_file (char const*,int /*<<< orphan*/ ,struct dentry*,struct dwc3_ep*,struct file_operations const*) ; 
 TYPE_1__* dwc3_ep_file_map ; 

__attribute__((used)) static void dwc3_debugfs_create_endpoint_files(struct dwc3_ep *dep,
		struct dentry *parent)
{
	int			i;

	for (i = 0; i < ARRAY_SIZE(dwc3_ep_file_map); i++) {
		const struct file_operations *fops = dwc3_ep_file_map[i].fops;
		const char *name = dwc3_ep_file_map[i].name;

		debugfs_create_file(name, S_IRUGO, parent, dep, fops);
	}
}