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
struct fei_attr {int /*<<< orphan*/  list; int /*<<< orphan*/  kp; } ;

/* Variables and functions */
 int /*<<< orphan*/  fei_attr_free (struct fei_attr*) ; 
 int /*<<< orphan*/  fei_debugfs_remove_attr (struct fei_attr*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_kprobe (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fei_attr_remove(struct fei_attr *attr)
{
	fei_debugfs_remove_attr(attr);
	unregister_kprobe(&attr->kp);
	list_del(&attr->list);
	fei_attr_free(attr);
}