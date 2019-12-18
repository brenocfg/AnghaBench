#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {char* data; } ;
struct TYPE_8__ {TYPE_1__* notifyTail; TYPE_1__* notifyHead; TYPE_3__ workBuffer; } ;
struct TYPE_7__ {char* relname; char* extra; int be_pid; struct TYPE_7__* next; } ;
typedef  TYPE_1__ PGnotify ;
typedef  TYPE_2__ PGconn ;

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ malloc (int) ; 
 scalar_t__ pqGetInt (int*,int,TYPE_2__*) ; 
 scalar_t__ pqGets (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 char* strdup (char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static int
getNotify(PGconn *conn)
{
	int			be_pid;
	char	   *svname;
	int			nmlen;
	int			extralen;
	PGnotify   *newNotify;

	if (pqGetInt(&be_pid, 4, conn))
		return EOF;
	if (pqGets(&conn->workBuffer, conn))
		return EOF;
	/* must save name while getting extra string */
	svname = strdup(conn->workBuffer.data);
	if (!svname)
		return EOF;
	if (pqGets(&conn->workBuffer, conn))
	{
		free(svname);
		return EOF;
	}

	/*
	 * Store the strings right after the PQnotify structure so it can all be
	 * freed at once.  We don't use NAMEDATALEN because we don't want to tie
	 * this interface to a specific server name length.
	 */
	nmlen = strlen(svname);
	extralen = strlen(conn->workBuffer.data);
	newNotify = (PGnotify *) malloc(sizeof(PGnotify) + nmlen + extralen + 2);
	if (newNotify)
	{
		newNotify->relname = (char *) newNotify + sizeof(PGnotify);
		strcpy(newNotify->relname, svname);
		newNotify->extra = newNotify->relname + nmlen + 1;
		strcpy(newNotify->extra, conn->workBuffer.data);
		newNotify->be_pid = be_pid;
		newNotify->next = NULL;
		if (conn->notifyTail)
			conn->notifyTail->next = newNotify;
		else
			conn->notifyHead = newNotify;
		conn->notifyTail = newNotify;
	}

	free(svname);
	return 0;
}