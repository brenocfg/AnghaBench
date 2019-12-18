#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  name; TYPE_2__* rconn; } ;
typedef  TYPE_1__ remoteConnHashEnt ;
struct TYPE_6__ {int /*<<< orphan*/  conn; } ;
typedef  TYPE_2__ remoteConn ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_DUPLICATE_OBJECT ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  HASH_ENTER ; 
 int /*<<< orphan*/  PQfinish (int /*<<< orphan*/ ) ; 
 scalar_t__ createConnHash () ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 scalar_t__ hash_search (scalar_t__,char*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pfree (TYPE_2__*) ; 
 char* pstrdup (char const*) ; 
 scalar_t__ remoteConnHash ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  truncate_identifier (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
createNewConnection(const char *name, remoteConn *rconn)
{
	remoteConnHashEnt *hentry;
	bool		found;
	char	   *key;

	if (!remoteConnHash)
		remoteConnHash = createConnHash();

	key = pstrdup(name);
	truncate_identifier(key, strlen(key), true);
	hentry = (remoteConnHashEnt *) hash_search(remoteConnHash, key,
											   HASH_ENTER, &found);

	if (found)
	{
		PQfinish(rconn->conn);
		pfree(rconn);

		ereport(ERROR,
				(errcode(ERRCODE_DUPLICATE_OBJECT),
				 errmsg("duplicate connection name")));
	}

	hentry->rconn = rconn;
	strlcpy(hentry->name, name, sizeof(hentry->name));
}