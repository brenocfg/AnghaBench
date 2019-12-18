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
struct key {int dummy; } ;
struct afs_cell {char* name; struct key* anonymous_key; } ;

/* Variables and functions */
 int /*<<< orphan*/  AFS_MAXCELLNAME ; 
 scalar_t__ IS_ERR (struct key*) ; 
 int PTR_ERR (struct key*) ; 
 int /*<<< orphan*/  _debug (char*,struct key*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  key_serial (struct key*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 struct key* rxrpc_get_null_key (char*) ; 
 int /*<<< orphan*/  tolower (char) ; 

__attribute__((used)) static int afs_alloc_anon_key(struct afs_cell *cell)
{
	struct key *key;
	char keyname[4 + AFS_MAXCELLNAME + 1], *cp, *dp;

	/* Create a key to represent an anonymous user. */
	memcpy(keyname, "afs@", 4);
	dp = keyname + 4;
	cp = cell->name;
	do {
		*dp++ = tolower(*cp);
	} while (*cp++);

	key = rxrpc_get_null_key(keyname);
	if (IS_ERR(key))
		return PTR_ERR(key);

	cell->anonymous_key = key;

	_debug("anon key %p{%x}",
	       cell->anonymous_key, key_serial(cell->anonymous_key));
	return 0;
}