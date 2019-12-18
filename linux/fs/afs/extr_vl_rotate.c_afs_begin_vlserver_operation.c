#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct key {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  error; } ;
struct afs_vl_cursor {int /*<<< orphan*/  flags; int /*<<< orphan*/  error; TYPE_1__ ac; struct key* key; struct afs_cell* cell; } ;
struct afs_cell {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AFS_VL_CURSOR_STOP ; 
 int /*<<< orphan*/  EDESTADDRREQ ; 
 int /*<<< orphan*/  EINTR ; 
 int /*<<< orphan*/  SHRT_MAX ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  memset (struct afs_vl_cursor*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 

bool afs_begin_vlserver_operation(struct afs_vl_cursor *vc, struct afs_cell *cell,
				  struct key *key)
{
	memset(vc, 0, sizeof(*vc));
	vc->cell = cell;
	vc->key = key;
	vc->error = -EDESTADDRREQ;
	vc->ac.error = SHRT_MAX;

	if (signal_pending(current)) {
		vc->error = -EINTR;
		vc->flags |= AFS_VL_CURSOR_STOP;
		return false;
	}

	return true;
}