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
typedef  int /*<<< orphan*/  nfs41_idmapper ;
typedef  int /*<<< orphan*/  gid_t ;
typedef  int DWORD ;

/* Variables and functions */
 int GetLastError () ; 
 int /*<<< orphan*/  GetUserNameA (char*,int*) ; 
 int NO_ERROR ; 
 int UNLEN ; 
 int /*<<< orphan*/  default_gid ; 
 int /*<<< orphan*/  default_uid ; 
 int /*<<< orphan*/  dprintf (int,char*,char*) ; 
 int /*<<< orphan*/  eprintf (char*,int) ; 
 scalar_t__ nfs41_idmap_name_to_ids (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int map_user_to_ids(nfs41_idmapper *idmapper, uid_t *uid, gid_t *gid)
{
    char username[UNLEN + 1];
    DWORD len = UNLEN + 1;
    int status = NO_ERROR;

    if (!GetUserNameA(username, &len)) {
        status = GetLastError();
        eprintf("GetUserName() failed with %d\n", status);
        goto out;
    }
    dprintf(1, "map_user_to_ids: mapping user %s\n", username);

    if (nfs41_idmap_name_to_ids(idmapper, username, uid, gid)) {
        /* instead of failing for auth_sys, fall back to 'nobody' uid/gid */
        *uid = default_uid;
        *gid = default_gid;
    }
out:
    return status;
}