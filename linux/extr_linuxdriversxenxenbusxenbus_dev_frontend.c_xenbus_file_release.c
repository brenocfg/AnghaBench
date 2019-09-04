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
struct xenbus_file_priv {int /*<<< orphan*/  kref; } ;
struct inode {int dummy; } ;
struct file {struct xenbus_file_priv* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xenbus_file_free ; 

__attribute__((used)) static int xenbus_file_release(struct inode *inode, struct file *filp)
{
	struct xenbus_file_priv *u = filp->private_data;

	kref_put(&u->kref, xenbus_file_free);

	return 0;
}