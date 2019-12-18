#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct file {int dummy; } ;
struct TYPE_4__ {TYPE_1__* nsproxy; } ;
struct TYPE_3__ {int /*<<< orphan*/  net_ns; } ;

/* Variables and functions */
 TYPE_2__* current ; 
 int exports_net_open (int /*<<< orphan*/ ,struct file*) ; 

__attribute__((used)) static int exports_proc_open(struct inode *inode, struct file *file)
{
	return exports_net_open(current->nsproxy->net_ns, file);
}