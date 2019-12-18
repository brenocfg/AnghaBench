#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sa ;
struct TYPE_5__ {scalar_t__ in_use; } ;
struct TYPE_4__ {int nLength; int /*<<< orphan*/  bInheritHandle; int /*<<< orphan*/ * lpSecurityDescriptor; } ;
typedef  TYPE_1__ SECURITY_ATTRIBUTES ;
typedef  void* HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/ * CreateMutex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  CreatePipe (void**,void**,TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ExecuteDetachedProgram (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,void*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/ * SniffEmacs ; 
 int /*<<< orphan*/  SniffEmacsReadThread ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (int /*<<< orphan*/ ) ; 
 scalar_t__ _beginthread (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  dup2 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  execvp (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exit (int) ; 
 int fd_from_sniff ; 
 int fd_to_sniff ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ ) ; 
 scalar_t__ fork () ; 
 int /*<<< orphan*/  fputs (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ gui ; 
 int /*<<< orphan*/  gui_exit (int) ; 
 int /*<<< orphan*/ * hBufferMutex ; 
 void* handle_from_sniff ; 
 void* handle_to_sniff ; 
 int /*<<< orphan*/  msg_sniff_disconnect ; 
 scalar_t__ pipe (int*) ; 
 void* readthread_handle ; 
 int /*<<< orphan*/  sleep (int) ; 
 int sniff_connected ; 
 scalar_t__ sniffemacs_handle ; 
 scalar_t__ sniffemacs_pid ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static int
ConnectToSniffEmacs()
{
#ifdef WIN32		/* Windows Version of the Code */
    HANDLE ToSniffEmacs[2], FromSniffEmacs[2];
    SECURITY_ATTRIBUTES sa;

    sa.nLength = sizeof(sa);
    sa.lpSecurityDescriptor = NULL;
    sa.bInheritHandle = TRUE;

    if (! CreatePipe(&ToSniffEmacs[0], &ToSniffEmacs[1], &sa, 0))
	return 1;
    if (! CreatePipe(&FromSniffEmacs[0], &FromSniffEmacs[1], &sa, 0))
	return 1;

    sniffemacs_handle = ExecuteDetachedProgram(SniffEmacs[0], SniffEmacs[0],
	ToSniffEmacs[0], FromSniffEmacs[1]);

    if (sniffemacs_handle)
    {
	handle_to_sniff  = ToSniffEmacs[1];
	handle_from_sniff = FromSniffEmacs[0];
	sniff_connected = 1;
	hBufferMutex = CreateMutex(
	    NULL,			/* no security attributes */
	    FALSE,			/* initially not owned */
	    "SniffReadBufferMutex");    /* name of mutex */
	if (hBufferMutex == NULL)
	{
	    /* Check for error. */
	}
	readthread_handle = (HANDLE)_beginthread(SniffEmacsReadThread, 0, NULL);
	return 0;
    }
    else
    {
	/* error in spawn() */
	return 1;
    }

#else		/* UNIX Version of the Code */
    int ToSniffEmacs[2], FromSniffEmacs[2];

    if (pipe(ToSniffEmacs) != 0)
	return 1;
    if (pipe(FromSniffEmacs) != 0)
	return 1;

    /* fork */
    if ((sniffemacs_pid=fork()) == 0)
    {
	/* child */

	/* prepare communication pipes */
	close(ToSniffEmacs[1]);
	close(FromSniffEmacs[0]);

	dup2(ToSniffEmacs[0],fileno(stdin));   /* write to ToSniffEmacs[1] */
	dup2(FromSniffEmacs[1],fileno(stdout));/* read from FromSniffEmacs[0] */

	close(ToSniffEmacs[0]);
	close(FromSniffEmacs[1]);

	/* start sniffemacs */
	execvp (SniffEmacs[0], SniffEmacs);
	{
/*	    FILE *out = fdopen(FromSniffEmacs[1], "w"); */
	    sleep(1);
	    fputs(_(msg_sniff_disconnect), stdout);
	    fflush(stdout);
	    sleep(3);
#ifdef FEAT_GUI
	    if (gui.in_use)
		gui_exit(1);
#endif
	    exit(1);
	}
	return 1;
    }
    else if (sniffemacs_pid > 0)
    {
	/* parent process */
	close(ToSniffEmacs[0]);
	fd_to_sniff  = ToSniffEmacs[1];
	close(FromSniffEmacs[1]);
	fd_from_sniff = FromSniffEmacs[0];
	sniff_connected = 1;
	return 0;
    }
    else   /* error in fork() */
	return 1;
#endif		/* UNIX Version of the Code */
}