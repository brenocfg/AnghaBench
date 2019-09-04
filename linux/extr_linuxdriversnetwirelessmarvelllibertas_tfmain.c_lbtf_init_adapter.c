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
struct lbtf_private {int /*<<< orphan*/  driver_lock; int /*<<< orphan*/  cmdpendingq; int /*<<< orphan*/  cmdfreeq; int /*<<< orphan*/  command_timer; int /*<<< orphan*/ * vif; int /*<<< orphan*/  lock; int /*<<< orphan*/  current_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LBTF_DEB_MAIN ; 
 int /*<<< orphan*/  command_timer_fn ; 
 int /*<<< orphan*/  eth_broadcast_addr (int /*<<< orphan*/ ) ; 
 scalar_t__ lbtf_allocate_cmd_buffer (struct lbtf_private*) ; 
 int /*<<< orphan*/  lbtf_deb_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbtf_deb_leave (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lbtf_init_adapter(struct lbtf_private *priv)
{
	lbtf_deb_enter(LBTF_DEB_MAIN);
	eth_broadcast_addr(priv->current_addr);
	mutex_init(&priv->lock);

	priv->vif = NULL;
	timer_setup(&priv->command_timer, command_timer_fn, 0);

	INIT_LIST_HEAD(&priv->cmdfreeq);
	INIT_LIST_HEAD(&priv->cmdpendingq);

	spin_lock_init(&priv->driver_lock);

	/* Allocate the command buffers */
	if (lbtf_allocate_cmd_buffer(priv))
		return -1;

	lbtf_deb_leave(LBTF_DEB_MAIN);
	return 0;
}