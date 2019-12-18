#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  owner; } ;
struct TYPE_4__ {TYPE_1__ nfs4_fl; } ;
struct file_lock {TYPE_2__ fl_u; } ;

/* Variables and functions */
 int /*<<< orphan*/  nfs4_put_lock_state (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nfs4_fl_release_lock(struct file_lock *fl)
{
	nfs4_put_lock_state(fl->fl_u.nfs4_fl.owner);
}