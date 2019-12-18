#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ pid_t ;
struct TYPE_11__ {int dead_end; int bgworker_notify; int /*<<< orphan*/  elem; int /*<<< orphan*/  bkend_type; scalar_t__ pid; scalar_t__ child_slot; int /*<<< orphan*/  cancel_key; } ;
struct TYPE_10__ {scalar_t__ canAcceptConnections; scalar_t__ sock; } ;
typedef  TYPE_1__ Port ;
typedef  TYPE_2__ Backend ;

/* Variables and functions */
 scalar_t__ AssignPostmasterChildSlot () ; 
 int /*<<< orphan*/  BACKEND_TYPE_NORMAL ; 
 int /*<<< orphan*/  BackendInitialize (TYPE_1__*) ; 
 int /*<<< orphan*/  BackendList ; 
 int /*<<< orphan*/  BackendRun (TYPE_1__*) ; 
 scalar_t__ CAC_OK ; 
 scalar_t__ CAC_WAITBACKUP ; 
 int /*<<< orphan*/  ClosePostmasterPorts (int) ; 
 int /*<<< orphan*/  DEBUG2 ; 
 int /*<<< orphan*/  ERRCODE_INTERNAL_ERROR ; 
 int /*<<< orphan*/  ERRCODE_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  InitPostmasterChild () ; 
 int /*<<< orphan*/  LOG ; 
 int /*<<< orphan*/  MyCancelKey ; 
 scalar_t__ MyPMChildSlot ; 
 int /*<<< orphan*/  RandomCancelKey (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleasePostmasterChildSlot (scalar_t__) ; 
 int STATUS_ERROR ; 
 int STATUS_OK ; 
 int /*<<< orphan*/  ShmemBackendArrayAdd (TYPE_2__*) ; 
 scalar_t__ backend_forkexec (TYPE_1__*) ; 
 scalar_t__ canAcceptConnections (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlist_push_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  errmsg_internal (char*,int,int) ; 
 int errno ; 
 scalar_t__ fork_process () ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  report_fork_failure_to_client (TYPE_1__*,int) ; 

__attribute__((used)) static int
BackendStartup(Port *port)
{
	Backend    *bn;				/* for backend cleanup */
	pid_t		pid;

	/*
	 * Create backend data structure.  Better before the fork() so we can
	 * handle failure cleanly.
	 */
	bn = (Backend *) malloc(sizeof(Backend));
	if (!bn)
	{
		ereport(LOG,
				(errcode(ERRCODE_OUT_OF_MEMORY),
				 errmsg("out of memory")));
		return STATUS_ERROR;
	}

	/*
	 * Compute the cancel key that will be assigned to this backend. The
	 * backend will have its own copy in the forked-off process' value of
	 * MyCancelKey, so that it can transmit the key to the frontend.
	 */
	if (!RandomCancelKey(&MyCancelKey))
	{
		free(bn);
		ereport(LOG,
				(errcode(ERRCODE_INTERNAL_ERROR),
				 errmsg("could not generate random cancel key")));
		return STATUS_ERROR;
	}

	bn->cancel_key = MyCancelKey;

	/* Pass down canAcceptConnections state */
	port->canAcceptConnections = canAcceptConnections(BACKEND_TYPE_NORMAL);
	bn->dead_end = (port->canAcceptConnections != CAC_OK &&
					port->canAcceptConnections != CAC_WAITBACKUP);

	/*
	 * Unless it's a dead_end child, assign it a child slot number
	 */
	if (!bn->dead_end)
		bn->child_slot = MyPMChildSlot = AssignPostmasterChildSlot();
	else
		bn->child_slot = 0;

	/* Hasn't asked to be notified about any bgworkers yet */
	bn->bgworker_notify = false;

#ifdef EXEC_BACKEND
	pid = backend_forkexec(port);
#else							/* !EXEC_BACKEND */
	pid = fork_process();
	if (pid == 0)				/* child */
	{
		free(bn);

		/* Detangle from postmaster */
		InitPostmasterChild();

		/* Close the postmaster's sockets */
		ClosePostmasterPorts(false);

		/* Perform additional initialization and collect startup packet */
		BackendInitialize(port);

		/* And run the backend */
		BackendRun(port);
	}
#endif							/* EXEC_BACKEND */

	if (pid < 0)
	{
		/* in parent, fork failed */
		int			save_errno = errno;

		if (!bn->dead_end)
			(void) ReleasePostmasterChildSlot(bn->child_slot);
		free(bn);
		errno = save_errno;
		ereport(LOG,
				(errmsg("could not fork new process for connection: %m")));
		report_fork_failure_to_client(port, save_errno);
		return STATUS_ERROR;
	}

	/* in parent, successful fork */
	ereport(DEBUG2,
			(errmsg_internal("forked new backend, pid=%d socket=%d",
							 (int) pid, (int) port->sock)));

	/*
	 * Everything's been successful, it's safe to add this backend to our list
	 * of backends.
	 */
	bn->pid = pid;
	bn->bkend_type = BACKEND_TYPE_NORMAL;	/* Can change later to WALSND */
	dlist_push_head(&BackendList, &bn->elem);

#ifdef EXEC_BACKEND
	if (!bn->dead_end)
		ShmemBackendArrayAdd(bn);
#endif

	return STATUS_OK;
}