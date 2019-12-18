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
typedef  int uid_t ;
typedef  int /*<<< orphan*/  machname ;
typedef  int gid_t ;
typedef  int /*<<< orphan*/  AUTH ;

/* Variables and functions */
 int /*<<< orphan*/  MAXHOSTNAMELEN ; 
 int NGRPS ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/ * authunix_create (char*,int,int,int,int*) ; 
 int getegid () ; 
 int geteuid () ; 
 int getgroups (int,int*) ; 
 int gethostname (char*,int) ; 

AUTH *
authunix_create_default()
{
	int len;
	char machname[MAXHOSTNAMELEN + 1];
	uid_t uid;
	gid_t gid;
	gid_t gids[NGRPS];

	if (gethostname(machname, sizeof machname) == -1)
		abort();
	machname[sizeof(machname) - 1] = 0;
#if 0
	uid = geteuid();
	gid = getegid();
	if ((len = getgroups(NGRPS, gids)) < 0)
		abort();
#else
	// XXX Need to figure out what to do here!
	uid = 666;
	gid = 777;
	gids[0] = 0;
	len = 0;
#endif
	/* XXX: interface problem; those should all have been unsigned */
	return (authunix_create(machname, uid, gid, len, gids));
}