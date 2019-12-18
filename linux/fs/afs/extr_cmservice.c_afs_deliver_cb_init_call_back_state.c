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
struct afs_call {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _enter (char*) ; 
 int afs_extract_data (struct afs_call*,int) ; 
 int /*<<< orphan*/  afs_extract_discard (struct afs_call*,int /*<<< orphan*/ ) ; 
 int afs_find_cm_server_by_peer (struct afs_call*) ; 

__attribute__((used)) static int afs_deliver_cb_init_call_back_state(struct afs_call *call)
{
	int ret;

	_enter("");

	afs_extract_discard(call, 0);
	ret = afs_extract_data(call, false);
	if (ret < 0)
		return ret;

	/* we'll need the file server record as that tells us which set of
	 * vnodes to operate upon */
	return afs_find_cm_server_by_peer(call);
}