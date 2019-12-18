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
typedef  int /*<<< orphan*/  remoteConnHashEnt ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_UNDEFINED_OBJECT ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  HASH_REMOVE ; 
 scalar_t__ createConnHash () ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 scalar_t__ hash_search (scalar_t__,char*,int /*<<< orphan*/ ,int*) ; 
 char* pstrdup (char const*) ; 
 scalar_t__ remoteConnHash ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  truncate_identifier (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
deleteConnection(const char *name)
{
	remoteConnHashEnt *hentry;
	bool		found;
	char	   *key;

	if (!remoteConnHash)
		remoteConnHash = createConnHash();

	key = pstrdup(name);
	truncate_identifier(key, strlen(key), false);
	hentry = (remoteConnHashEnt *) hash_search(remoteConnHash,
											   key, HASH_REMOVE, &found);

	if (!hentry)
		ereport(ERROR,
				(errcode(ERRCODE_UNDEFINED_OBJECT),
				 errmsg("undefined connection name")));

}