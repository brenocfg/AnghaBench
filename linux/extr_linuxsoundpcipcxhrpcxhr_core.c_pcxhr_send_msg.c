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
struct pcxhr_rmh {int dummy; } ;
struct pcxhr_mgr {int /*<<< orphan*/  msg_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int pcxhr_send_msg_nolock (struct pcxhr_mgr*,struct pcxhr_rmh*) ; 

int pcxhr_send_msg(struct pcxhr_mgr *mgr, struct pcxhr_rmh *rmh)
{
	int err;

	mutex_lock(&mgr->msg_lock);
	err = pcxhr_send_msg_nolock(mgr, rmh);
	mutex_unlock(&mgr->msg_lock);
	return err;
}