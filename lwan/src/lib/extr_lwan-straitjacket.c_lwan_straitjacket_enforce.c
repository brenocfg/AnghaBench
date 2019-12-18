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
struct lwan_straitjacket {scalar_t__ drop_capabilities; scalar_t__* user_name; scalar_t__ chroot_path; } ;
struct __user_cap_header_struct {int /*<<< orphan*/  version; } ;
struct __user_cap_data_struct {int dummy; } ;
typedef  int /*<<< orphan*/  gid_t ;

/* Variables and functions */
 int /*<<< orphan*/  _LINUX_CAPABILITY_VERSION_1 ; 
 int /*<<< orphan*/  abort_on_open_directories () ; 
 scalar_t__ capset (struct __user_cap_header_struct*,struct __user_cap_data_struct*) ; 
 scalar_t__ chdir (char*) ; 
 scalar_t__ chroot (scalar_t__) ; 
 int /*<<< orphan*/  get_user_uid_gid (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ geteuid () ; 
 int /*<<< orphan*/  lwan_status_critical (char*,...) ; 
 int /*<<< orphan*/  lwan_status_critical_perror (char*,...) ; 
 int /*<<< orphan*/  lwan_status_info (char*,scalar_t__) ; 
 int /*<<< orphan*/  switch_to_user (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 

void lwan_straitjacket_enforce(const struct lwan_straitjacket *sj)
{
    uid_t uid = 0;
    gid_t gid = 0;
    bool got_uid_gid = false;

    if (!sj->user_name && !sj->chroot_path)
        goto out;

    if (geteuid() != 0)
        lwan_status_critical("Straitjacket requires root privileges");

    if (sj->user_name && *sj->user_name) {
        if (!get_user_uid_gid(sj->user_name, &uid, &gid))
            lwan_status_critical("Unknown user: %s", sj->user_name);
        got_uid_gid = true;
    }

    if (sj->chroot_path) {
        abort_on_open_directories();

        if (chroot(sj->chroot_path) < 0) {
            lwan_status_critical_perror("Could not chroot() to %s",
                                        sj->chroot_path);
        }

        if (chdir("/") < 0)
            lwan_status_critical_perror("Could not chdir() to /");

        lwan_status_info("Jailed to %s", sj->chroot_path);
    }

    if (got_uid_gid) {
        if (!switch_to_user(uid, gid, sj->user_name))
            lwan_status_critical("Could not drop privileges to %s, aborting",
                                 sj->user_name);
    }

out:
    if (sj->drop_capabilities) {
        struct __user_cap_header_struct header = {
            .version = _LINUX_CAPABILITY_VERSION_1
        };
        struct __user_cap_data_struct data = {};

        if (capset(&header, &data) < 0)
            lwan_status_critical_perror("Could not drop capabilities");
    }
}