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
struct vmlogrdr_priv_t {int connection_established; int /*<<< orphan*/  priv_lock; } ;
struct iucv_path {struct vmlogrdr_priv_t* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  conn_wait_queue ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vmlogrdr_iucv_path_complete(struct iucv_path *path, u8 *ipuser)
{
	struct vmlogrdr_priv_t * logptr = path->private;

	spin_lock(&logptr->priv_lock);
	logptr->connection_established = 1;
	spin_unlock(&logptr->priv_lock);
	wake_up(&conn_wait_queue);
}