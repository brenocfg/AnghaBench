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
struct TYPE_2__ {int /*<<< orphan*/ * rconn; } ;
typedef  TYPE_1__ remoteConnHashEnt ;
typedef  int /*<<< orphan*/  remoteConn ;

/* Variables and functions */
 int /*<<< orphan*/  HASH_FIND ; 
 scalar_t__ createConnHash () ; 
 scalar_t__ hash_search (scalar_t__,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* pstrdup (char const*) ; 
 scalar_t__ remoteConnHash ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  truncate_identifier (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static remoteConn *
getConnectionByName(const char *name)
{
	remoteConnHashEnt *hentry;
	char	   *key;

	if (!remoteConnHash)
		remoteConnHash = createConnHash();

	key = pstrdup(name);
	truncate_identifier(key, strlen(key), false);
	hentry = (remoteConnHashEnt *) hash_search(remoteConnHash,
											   key, HASH_FIND, NULL);

	if (hentry)
		return hentry->rconn;

	return NULL;
}