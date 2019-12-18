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
struct passwd {int /*<<< orphan*/  pw_gid; int /*<<< orphan*/  pw_uid; } ;
typedef  int /*<<< orphan*/  gid_t ;

/* Variables and functions */
 long NSS_BUFLEN_PASSWD ; 
 int /*<<< orphan*/  _SC_GETPW_R_SIZE_MAX ; 
 int errno ; 
 int /*<<< orphan*/  free (char*) ; 
 int getpwnam_r (char const*,struct passwd*,char*,size_t,struct passwd**) ; 
 int /*<<< orphan*/  lwan_status_error (char*,...) ; 
 int /*<<< orphan*/  lwan_status_perror (char*,char const*) ; 
 char* malloc (size_t) ; 
 long sysconf (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool get_user_uid_gid(const char *user, uid_t *uid, gid_t *gid)
{
    struct passwd pwd = {};
    struct passwd *result;
    char *buf;
    long pw_size_max = sysconf(_SC_GETPW_R_SIZE_MAX);
    int r;

    if (pw_size_max < 0) {
        /* This constant is returned for sysconf(_SC_GETPW_R_SIZE_MAX) in glibc,
         * and it seems to be a reasonable size (1024).  Use it as a fallback in
         * the (very unlikely) case where sysconf() fails. */
        pw_size_max = NSS_BUFLEN_PASSWD;
    }

    buf = malloc((size_t)pw_size_max);
    if (!buf) {
        lwan_status_error("Could not allocate buffer for passwd struct");
        return false;
    }

    r = getpwnam_r(user, &pwd, buf, (size_t)pw_size_max, &result);
    *uid = pwd.pw_uid;
    *gid = pwd.pw_gid;
    free(buf);

    if (result)
        return true;

    if (!r) {
        lwan_status_error("Username not found: %s", user);
    } else {
        errno = r;
        lwan_status_perror("Could not obtain uid/gid for user %s", user);
    }

    return false;
}