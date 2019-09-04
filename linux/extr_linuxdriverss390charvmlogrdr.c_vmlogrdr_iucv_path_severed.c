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
typedef  int /*<<< orphan*/  u8 ;
struct vmlogrdr_priv_t {int iucv_path_severed; int /*<<< orphan*/  priv_lock; scalar_t__ connection_established; int /*<<< orphan*/ * path; } ;
struct iucv_path {struct vmlogrdr_priv_t* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  conn_wait_queue ; 
 int /*<<< orphan*/  iucv_path_sever (struct iucv_path*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct iucv_path*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_wait_queue ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vmlogrdr_iucv_path_severed(struct iucv_path *path, u8 *ipuser)
{
	struct vmlogrdr_priv_t * logptr = path->private;
	u8 reason = (u8) ipuser[8];

	pr_err("vmlogrdr: connection severed with reason %i\n", reason);

	iucv_path_sever(path, NULL);
	kfree(path);
	logptr->path = NULL;

	spin_lock(&logptr->priv_lock);
	logptr->connection_established = 0;
	logptr->iucv_path_severed = 1;
	spin_unlock(&logptr->priv_lock);

	wake_up(&conn_wait_queue);
	/* just in case we're sleeping waiting for a record */
	wake_up_interruptible(&read_wait_queue);
}