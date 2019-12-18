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
struct o2net_status_wait {int /*<<< orphan*/  ns_node_item; } ;
struct o2net_node {int /*<<< orphan*/  nn_lock; } ;

/* Variables and functions */
 int list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int o2net_nsw_completed(struct o2net_node *nn,
			       struct o2net_status_wait *nsw)
{
	int completed;
	spin_lock(&nn->nn_lock);
	completed = list_empty(&nsw->ns_node_item);
	spin_unlock(&nn->nn_lock);
	return completed;
}