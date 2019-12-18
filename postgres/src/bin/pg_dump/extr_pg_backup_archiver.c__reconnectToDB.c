#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/ * currTablespace; int /*<<< orphan*/ * currSchema; int /*<<< orphan*/ * currUser; } ;
struct TYPE_11__ {char* data; } ;
typedef  TYPE_1__ PQExpBufferData ;
typedef  TYPE_2__ ArchiveHandle ;

/* Variables and functions */
 int /*<<< orphan*/  ReconnectToServer (TYPE_2__*,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ RestoringToDB (TYPE_2__*) ; 
 int /*<<< orphan*/  _doSetFixedOutputState (TYPE_2__*) ; 
 int /*<<< orphan*/  ahprintf (TYPE_2__*,char*,char*) ; 
 int /*<<< orphan*/  appendPsqlMetaConnect (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  initPQExpBuffer (TYPE_1__*) ; 
 int /*<<< orphan*/  termPQExpBuffer (TYPE_1__*) ; 

__attribute__((used)) static void
_reconnectToDB(ArchiveHandle *AH, const char *dbname)
{
	if (RestoringToDB(AH))
		ReconnectToServer(AH, dbname, NULL);
	else
	{
		if (dbname)
		{
			PQExpBufferData connectbuf;

			initPQExpBuffer(&connectbuf);
			appendPsqlMetaConnect(&connectbuf, dbname);
			ahprintf(AH, "%s\n", connectbuf.data);
			termPQExpBuffer(&connectbuf);
		}
		else
			ahprintf(AH, "%s\n", "\\connect -\n");
	}

	/*
	 * NOTE: currUser keeps track of what the imaginary session user in our
	 * script is.  It's now effectively reset to the original userID.
	 */
	if (AH->currUser)
		free(AH->currUser);
	AH->currUser = NULL;

	/* don't assume we still know the output schema, tablespace, etc either */
	if (AH->currSchema)
		free(AH->currSchema);
	AH->currSchema = NULL;
	if (AH->currTablespace)
		free(AH->currTablespace);
	AH->currTablespace = NULL;

	/* re-establish fixed state */
	_doSetFixedOutputState(AH);
}