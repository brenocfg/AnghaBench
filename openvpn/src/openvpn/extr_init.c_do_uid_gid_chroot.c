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
struct context_0 {int uid_gid_chroot_set; int /*<<< orphan*/  platform_state_user; int /*<<< orphan*/  platform_state_group; scalar_t__ uid_gid_specified; } ;
struct TYPE_2__ {char const* selinux_context; scalar_t__ memstats_fn; scalar_t__ chroot_dir; } ;
struct context {scalar_t__ first_time; TYPE_1__ options; struct context_0* c0; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_ERR ; 
 int /*<<< orphan*/  M_INFO ; 
 int /*<<< orphan*/  msg (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  mstats_open (scalar_t__) ; 
 int /*<<< orphan*/  platform_chroot (scalar_t__) ; 
 int /*<<< orphan*/  platform_group_set (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_user_set (int /*<<< orphan*/ *) ; 
 int setcon (char const*) ; 

__attribute__((used)) static void
do_uid_gid_chroot(struct context *c, bool no_delay)
{
    static const char why_not[] = "will be delayed because of --client, --pull, or --up-delay";
    struct context_0 *c0 = c->c0;

    if (c0 && !c0->uid_gid_chroot_set)
    {
        /* chroot if requested */
        if (c->options.chroot_dir)
        {
            if (no_delay)
            {
                platform_chroot(c->options.chroot_dir);
            }
            else if (c->first_time)
            {
                msg(M_INFO, "NOTE: chroot %s", why_not);
            }
        }

        /* set user and/or group if we want to setuid/setgid */
        if (c0->uid_gid_specified)
        {
            if (no_delay)
            {
                platform_group_set(&c0->platform_state_group);
                platform_user_set(&c0->platform_state_user);
            }
            else if (c->first_time)
            {
                msg(M_INFO, "NOTE: UID/GID downgrade %s", why_not);
            }
        }

#ifdef ENABLE_MEMSTATS
        if (c->first_time && c->options.memstats_fn)
        {
            mstats_open(c->options.memstats_fn);
        }
#endif

#ifdef ENABLE_SELINUX
        /* Apply a SELinux context in order to restrict what OpenVPN can do
         * to _only_ what it is supposed to do after initialization is complete
         * (basically just network I/O operations). Doing it after chroot
         * requires /proc to be mounted in the chroot (which is annoying indeed
         * but doing it before requires more complex SELinux policies.
         */
        if (c->options.selinux_context)
        {
            if (no_delay)
            {
                if (-1 == setcon(c->options.selinux_context))
                {
                    msg(M_ERR, "setcon to '%s' failed; is /proc accessible?", c->options.selinux_context);
                }
                else
                {
                    msg(M_INFO, "setcon to '%s' succeeded", c->options.selinux_context);
                }
            }
            else if (c->first_time)
            {
                msg(M_INFO, "NOTE: setcon %s", why_not);
            }
        }
#endif

        /* Privileges are going to be dropped by now (if requested), be sure
         * to prevent any future privilege dropping attempts from now on.
         */
        if (no_delay)
        {
            c0->uid_gid_chroot_set = true;
        }
    }
}