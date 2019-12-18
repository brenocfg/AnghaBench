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
struct TYPE_2__ {int said_rebooted; scalar_t__ cm_epoch; int cm_probed; int said_inconsistent; } ;
struct afs_server {scalar_t__ cm_epoch; int /*<<< orphan*/  probe_lock; TYPE_1__ probe; int /*<<< orphan*/  uuid; int /*<<< orphan*/  flags; } ;
struct afs_call {scalar_t__ epoch; } ;

/* Variables and functions */
 int /*<<< orphan*/  AFS_SERVER_FL_HAVE_EPOCH ; 
 int /*<<< orphan*/  AFS_SERVER_FL_PROBING ; 
 int /*<<< orphan*/  _enter (char*) ; 
 int /*<<< orphan*/  pr_notice (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int afs_record_cm_probe(struct afs_call *call, struct afs_server *server)
{
	_enter("");

	if (test_bit(AFS_SERVER_FL_HAVE_EPOCH, &server->flags) &&
	    !test_bit(AFS_SERVER_FL_PROBING, &server->flags)) {
		if (server->cm_epoch == call->epoch)
			return 0;

		if (!server->probe.said_rebooted) {
			pr_notice("kAFS: FS rebooted %pU\n", &server->uuid);
			server->probe.said_rebooted = true;
		}
	}

	spin_lock(&server->probe_lock);

	if (!test_bit(AFS_SERVER_FL_HAVE_EPOCH, &server->flags)) {
		server->cm_epoch = call->epoch;
		server->probe.cm_epoch = call->epoch;
		goto out;
	}

	if (server->probe.cm_probed &&
	    call->epoch != server->probe.cm_epoch &&
	    !server->probe.said_inconsistent) {
		pr_notice("kAFS: FS endpoints inconsistent %pU\n",
			  &server->uuid);
		server->probe.said_inconsistent = true;
	}

	if (!server->probe.cm_probed || call->epoch == server->cm_epoch)
		server->probe.cm_epoch = server->cm_epoch;

out:
	server->probe.cm_probed = true;
	spin_unlock(&server->probe_lock);
	return 0;
}