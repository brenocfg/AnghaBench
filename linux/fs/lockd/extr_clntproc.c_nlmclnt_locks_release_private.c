#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_4__* owner; int /*<<< orphan*/  list; } ;
struct TYPE_5__ {TYPE_3__ nfs_fl; } ;
struct file_lock {TYPE_1__ fl_u; } ;
struct TYPE_8__ {TYPE_2__* host; } ;
struct TYPE_6__ {int /*<<< orphan*/  h_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nlmclnt_put_lockowner (TYPE_4__*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nlmclnt_locks_release_private(struct file_lock *fl)
{
	spin_lock(&fl->fl_u.nfs_fl.owner->host->h_lock);
	list_del(&fl->fl_u.nfs_fl.list);
	spin_unlock(&fl->fl_u.nfs_fl.owner->host->h_lock);
	nlmclnt_put_lockowner(fl->fl_u.nfs_fl.owner);
}