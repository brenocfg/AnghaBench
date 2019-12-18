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

/* Variables and functions */
 int /*<<< orphan*/  M_ERR ; 
 int /*<<< orphan*/  M_FATAL ; 
 int /*<<< orphan*/  M_INFO ; 
 scalar_t__ chroot (char const*) ; 
 int /*<<< orphan*/  msg (int /*<<< orphan*/ ,char*,char const*,...) ; 
 scalar_t__ platform_chdir (char const*) ; 

void
platform_chroot(const char *path)
{
    if (path)
    {
#ifdef HAVE_CHROOT
        const char *top = "/";
        if (chroot(path))
        {
            msg(M_ERR, "chroot to '%s' failed", path);
        }
        if (platform_chdir(top))
        {
            msg(M_ERR, "cd to '%s' failed", top);
        }
        msg(M_INFO, "chroot to '%s' and cd to '%s' succeeded", path, top);
#else  /* ifdef HAVE_CHROOT */
        msg(M_FATAL, "Sorry but I can't chroot to '%s' because this operating system doesn't appear to support the chroot() system call", path);
#endif
    }
}