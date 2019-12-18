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
typedef  int /*<<< orphan*/  ucred_t ;
struct xucred {scalar_t__ cr_version; int /*<<< orphan*/  cr_gid; int /*<<< orphan*/  cr_uid; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; } ;
struct ucred {scalar_t__ cr_version; int /*<<< orphan*/  cr_gid; int /*<<< orphan*/  cr_uid; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; } ;
typedef  int /*<<< orphan*/  peercred ;
typedef  int /*<<< orphan*/  gid_t ;
typedef  int ACCEPT_TYPE_ARG3 ;

/* Variables and functions */
 int /*<<< orphan*/  ENOSYS ; 
 int /*<<< orphan*/  LOCAL_PEERCRED ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_PEERCRED ; 
 scalar_t__ XUCRED_VERSION ; 
 int /*<<< orphan*/  errno ; 
 int getpeerucred (int,int /*<<< orphan*/ **) ; 
 scalar_t__ getsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct xucred*,int*) ; 
 int /*<<< orphan*/  ucred_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ucred_getegid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ucred_geteuid (int /*<<< orphan*/ *) ; 

int
getpeereid(int sock, uid_t *uid, gid_t *gid)
{
#if defined(SO_PEERCRED)
	/* Linux: use getsockopt(SO_PEERCRED) */
	struct ucred peercred;
	ACCEPT_TYPE_ARG3 so_len = sizeof(peercred);

	if (getsockopt(sock, SOL_SOCKET, SO_PEERCRED, &peercred, &so_len) != 0 ||
		so_len != sizeof(peercred))
		return -1;
	*uid = peercred.uid;
	*gid = peercred.gid;
	return 0;
#elif defined(LOCAL_PEERCRED)
	/* Debian with FreeBSD kernel: use getsockopt(LOCAL_PEERCRED) */
	struct xucred peercred;
	ACCEPT_TYPE_ARG3 so_len = sizeof(peercred);

	if (getsockopt(sock, 0, LOCAL_PEERCRED, &peercred, &so_len) != 0 ||
		so_len != sizeof(peercred) ||
		peercred.cr_version != XUCRED_VERSION)
		return -1;
	*uid = peercred.cr_uid;
	*gid = peercred.cr_gid;
	return 0;
#elif defined(HAVE_GETPEERUCRED)
	/* Solaris: use getpeerucred() */
	ucred_t    *ucred;

	ucred = NULL;				/* must be initialized to NULL */
	if (getpeerucred(sock, &ucred) == -1)
		return -1;

	*uid = ucred_geteuid(ucred);
	*gid = ucred_getegid(ucred);
	ucred_free(ucred);

	if (*uid == (uid_t) (-1) || *gid == (gid_t) (-1))
		return -1;
	return 0;
#else
	/* No implementation available on this platform */
	errno = ENOSYS;
	return -1;
#endif
}