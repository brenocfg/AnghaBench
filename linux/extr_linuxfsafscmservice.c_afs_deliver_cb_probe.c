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
 int /*<<< orphan*/  AFS_CALL_SV_REPLYING ; 
 int EIO ; 
 int /*<<< orphan*/  _enter (char*) ; 
 int /*<<< orphan*/  afs_check_call_state (struct afs_call*,int /*<<< orphan*/ ) ; 
 int afs_extract_data (struct afs_call*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int afs_queue_call_work (struct afs_call*) ; 

__attribute__((used)) static int afs_deliver_cb_probe(struct afs_call *call)
{
	int ret;

	_enter("");

	ret = afs_extract_data(call, NULL, 0, false);
	if (ret < 0)
		return ret;

	if (!afs_check_call_state(call, AFS_CALL_SV_REPLYING))
		return -EIO;

	return afs_queue_call_work(call);
}