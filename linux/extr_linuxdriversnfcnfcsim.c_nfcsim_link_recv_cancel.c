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
struct nfcsim_link {int /*<<< orphan*/  lock; int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFCSIM_MODE_NONE ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfcsim_link_recv_wake (struct nfcsim_link*) ; 

__attribute__((used)) static void nfcsim_link_recv_cancel(struct nfcsim_link *link)
{
	mutex_lock(&link->lock);

	link->mode = NFCSIM_MODE_NONE;

	mutex_unlock(&link->lock);

	nfcsim_link_recv_wake(link);
}