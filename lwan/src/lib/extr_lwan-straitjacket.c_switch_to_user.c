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
typedef  scalar_t__ uid_t ;
typedef  scalar_t__ gid_t ;

/* Variables and functions */
 scalar_t__ getresgid (scalar_t__*,scalar_t__*,scalar_t__*) ; 
 scalar_t__ getresuid (scalar_t__*,scalar_t__*,scalar_t__*) ; 
 scalar_t__ initgroups (char const*,scalar_t__) ; 
 int /*<<< orphan*/  lwan_status_info (char*,scalar_t__,scalar_t__,char const*) ; 
 scalar_t__ setresgid (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ setresuid (scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static bool switch_to_user(uid_t uid, gid_t gid, const char *username)
{
    uid_t ruid, euid, suid;
    gid_t rgid, egid, sgid;

    lwan_status_info("Dropping privileges to UID %d, GID %d (%s)",
        uid, gid, username);

    if (setresgid(gid, gid, gid) < 0)
        return false;
#if defined(__APPLE__)
    if (initgroups(username, (int)gid) < 0)
        return false;
#else
    if (initgroups(username, gid) < 0)
        return false;
#endif
    if (setresuid(uid, uid, uid) < 0)
        return false;

    if (getresuid(&ruid, &euid, &suid) < 0)
        return false;
    if (ruid != euid || euid != suid || suid != uid)
        return false;

    if (getresgid(&rgid, &egid, &sgid) < 0)
        return false;
    if (rgid != egid || egid != sgid || sgid != gid)
        return false;

    return true;
}