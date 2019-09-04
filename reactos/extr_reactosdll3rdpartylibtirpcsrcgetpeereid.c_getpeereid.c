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
typedef  int /*<<< orphan*/  uid_t ;
typedef  int /*<<< orphan*/  uc ;
struct ucred {int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  gid_t ;

/* Variables and functions */
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_PEERCRED ; 
 int getsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ucred*,int*) ; 

int
getpeereid(int s, uid_t *euid, gid_t *egid)
{
	struct ucred uc;
	socklen_t uclen;
	int error;

	uclen = sizeof(uc); 
	error = getsockopt(s, SOL_SOCKET, SO_PEERCRED, &uc, &uclen); /*  SCM_CREDENTIALS */
	if (error != 0)
		return (error);
	//	if (uc.cr_version != XUCRED_VERSION)
	//	return (EINVAL);
	*euid = uc.uid;
	*egid = uc.gid;
	return (0);
 }