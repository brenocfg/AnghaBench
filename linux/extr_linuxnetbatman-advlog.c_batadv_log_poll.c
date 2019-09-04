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
struct file {struct batadv_priv* private_data; } ;
struct batadv_priv_debug_log {int /*<<< orphan*/  queue_wait; } ;
struct batadv_priv {struct batadv_priv_debug_log* debug_log; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int __poll_t ;

/* Variables and functions */
 int EPOLLIN ; 
 int EPOLLRDNORM ; 
 int /*<<< orphan*/  batadv_log_empty (struct batadv_priv_debug_log*) ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static __poll_t batadv_log_poll(struct file *file, poll_table *wait)
{
	struct batadv_priv *bat_priv = file->private_data;
	struct batadv_priv_debug_log *debug_log = bat_priv->debug_log;

	poll_wait(file, &debug_log->queue_wait, wait);

	if (!batadv_log_empty(debug_log))
		return EPOLLIN | EPOLLRDNORM;

	return 0;
}