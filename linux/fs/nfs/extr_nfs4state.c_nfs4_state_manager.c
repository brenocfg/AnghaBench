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
struct nfs_client {int /*<<< orphan*/  cl_hostname; int /*<<< orphan*/  cl_state; TYPE_1__* cl_mvops; int /*<<< orphan*/  cl_count; } ;
struct TYPE_2__ {int /*<<< orphan*/  nograce_recovery_ops; int /*<<< orphan*/  reboot_recovery_ops; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  NFS4CLNT_BIND_CONN_TO_SESSION ; 
 int /*<<< orphan*/  NFS4CLNT_CHECK_LEASE ; 
 int /*<<< orphan*/  NFS4CLNT_DELEGATION_EXPIRED ; 
 int /*<<< orphan*/  NFS4CLNT_DELEGRETURN ; 
 int /*<<< orphan*/  NFS4CLNT_DELEGRETURN_RUNNING ; 
 int /*<<< orphan*/  NFS4CLNT_LEASE_EXPIRED ; 
 int /*<<< orphan*/  NFS4CLNT_LEASE_MOVED ; 
 int /*<<< orphan*/  NFS4CLNT_MANAGER_RUNNING ; 
 int /*<<< orphan*/  NFS4CLNT_MOVED ; 
 int /*<<< orphan*/  NFS4CLNT_PURGE_STATE ; 
 int /*<<< orphan*/  NFS4CLNT_RECLAIM_NOGRACE ; 
 int /*<<< orphan*/  NFS4CLNT_RECLAIM_REBOOT ; 
 int /*<<< orphan*/  NFS4CLNT_RUN_MANAGER ; 
 int /*<<< orphan*/  NFS4CLNT_SESSION_RESET ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int nfs4_bind_conn_to_session (struct nfs_client*) ; 
 int nfs4_check_lease (struct nfs_client*) ; 
 int /*<<< orphan*/  nfs4_clear_state_manager_bit (struct nfs_client*) ; 
 int nfs4_do_reclaim (struct nfs_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs4_end_drain_session (struct nfs_client*) ; 
 int nfs4_handle_lease_moved (struct nfs_client*) ; 
 int nfs4_handle_migration (struct nfs_client*) ; 
 int nfs4_purge_lease (struct nfs_client*) ; 
 int nfs4_reclaim_lease (struct nfs_client*) ; 
 int nfs4_reset_session (struct nfs_client*) ; 
 int /*<<< orphan*/  nfs4_state_end_reclaim_reboot (struct nfs_client*) ; 
 int /*<<< orphan*/  nfs_client_return_marked_delegations (struct nfs_client*) ; 
 int /*<<< orphan*/  nfs_reap_expired_delegations (struct nfs_client*) ; 
 int /*<<< orphan*/  pr_warn_ratelimited (char*,char const*,char const*,int /*<<< orphan*/ ,int) ; 
 int refcount_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  signalled () ; 
 int /*<<< orphan*/  ssleep (int) ; 
 scalar_t__ strlen (char const*) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nfs4_state_manager(struct nfs_client *clp)
{
	int status = 0;
	const char *section = "", *section_sep = "";

	/* Ensure exclusive access to NFSv4 state */
	do {
		clear_bit(NFS4CLNT_RUN_MANAGER, &clp->cl_state);
		if (test_bit(NFS4CLNT_PURGE_STATE, &clp->cl_state)) {
			section = "purge state";
			status = nfs4_purge_lease(clp);
			if (status < 0)
				goto out_error;
			continue;
		}

		if (test_bit(NFS4CLNT_LEASE_EXPIRED, &clp->cl_state)) {
			section = "lease expired";
			/* We're going to have to re-establish a clientid */
			status = nfs4_reclaim_lease(clp);
			if (status < 0)
				goto out_error;
			continue;
		}

		/* Initialize or reset the session */
		if (test_and_clear_bit(NFS4CLNT_SESSION_RESET, &clp->cl_state)) {
			section = "reset session";
			status = nfs4_reset_session(clp);
			if (test_bit(NFS4CLNT_LEASE_EXPIRED, &clp->cl_state))
				continue;
			if (status < 0)
				goto out_error;
		}

		/* Send BIND_CONN_TO_SESSION */
		if (test_and_clear_bit(NFS4CLNT_BIND_CONN_TO_SESSION,
				&clp->cl_state)) {
			section = "bind conn to session";
			status = nfs4_bind_conn_to_session(clp);
			if (status < 0)
				goto out_error;
			continue;
		}

		if (test_and_clear_bit(NFS4CLNT_CHECK_LEASE, &clp->cl_state)) {
			section = "check lease";
			status = nfs4_check_lease(clp);
			if (status < 0)
				goto out_error;
			continue;
		}

		if (test_and_clear_bit(NFS4CLNT_MOVED, &clp->cl_state)) {
			section = "migration";
			status = nfs4_handle_migration(clp);
			if (status < 0)
				goto out_error;
		}

		if (test_and_clear_bit(NFS4CLNT_LEASE_MOVED, &clp->cl_state)) {
			section = "lease moved";
			status = nfs4_handle_lease_moved(clp);
			if (status < 0)
				goto out_error;
		}

		/* First recover reboot state... */
		if (test_bit(NFS4CLNT_RECLAIM_REBOOT, &clp->cl_state)) {
			section = "reclaim reboot";
			status = nfs4_do_reclaim(clp,
				clp->cl_mvops->reboot_recovery_ops);
			if (status == -EAGAIN)
				continue;
			if (status < 0)
				goto out_error;
			nfs4_state_end_reclaim_reboot(clp);
		}

		/* Detect expired delegations... */
		if (test_and_clear_bit(NFS4CLNT_DELEGATION_EXPIRED, &clp->cl_state)) {
			section = "detect expired delegations";
			nfs_reap_expired_delegations(clp);
			continue;
		}

		/* Now recover expired state... */
		if (test_bit(NFS4CLNT_RECLAIM_NOGRACE, &clp->cl_state)) {
			section = "reclaim nograce";
			status = nfs4_do_reclaim(clp,
				clp->cl_mvops->nograce_recovery_ops);
			if (status == -EAGAIN)
				continue;
			if (status < 0)
				goto out_error;
			clear_bit(NFS4CLNT_RECLAIM_NOGRACE, &clp->cl_state);
		}

		nfs4_end_drain_session(clp);
		nfs4_clear_state_manager_bit(clp);

		if (!test_and_set_bit(NFS4CLNT_DELEGRETURN_RUNNING, &clp->cl_state)) {
			if (test_and_clear_bit(NFS4CLNT_DELEGRETURN, &clp->cl_state)) {
				nfs_client_return_marked_delegations(clp);
				set_bit(NFS4CLNT_RUN_MANAGER, &clp->cl_state);
			}
			clear_bit(NFS4CLNT_DELEGRETURN_RUNNING, &clp->cl_state);
		}

		/* Did we race with an attempt to give us more work? */
		if (!test_bit(NFS4CLNT_RUN_MANAGER, &clp->cl_state))
			return;
		if (test_and_set_bit(NFS4CLNT_MANAGER_RUNNING, &clp->cl_state) != 0)
			return;
	} while (refcount_read(&clp->cl_count) > 1 && !signalled());
	goto out_drain;

out_error:
	if (strlen(section))
		section_sep = ": ";
	pr_warn_ratelimited("NFS: state manager%s%s failed on NFSv4 server %s"
			" with error %d\n", section_sep, section,
			clp->cl_hostname, -status);
	ssleep(1);
out_drain:
	nfs4_end_drain_session(clp);
	nfs4_clear_state_manager_bit(clp);
}