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
struct gc_arena {int dummy; } ;
struct buffer {int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 char const* BSTR (struct buffer*) ; 
 char const* PATH_SEPARATOR_STR ; 
 struct buffer alloc_buf_gc (int,struct gc_arena*) ; 
 int /*<<< orphan*/  buf_printf (struct buffer*,char*,char const*,char const*,char const*) ; 
 int check_file_access (int const,char const*,int const,char const*) ; 
 int /*<<< orphan*/  gc_free (struct gc_arena*) ; 
 struct gc_arena gc_new () ; 
 int strlen (char const*) ; 

__attribute__((used)) static bool
check_file_access_chroot(const char *chroot, const int type, const char *file, const int mode, const char *opt)
{
    bool ret = false;

    /* If no file configured, no errors to look for */
    if (!file)
    {
        return false;
    }

    /* If chroot is set, look for the file/directory inside the chroot */
    if (chroot)
    {
        struct gc_arena gc = gc_new();
        struct buffer chroot_file;
        int len = 0;

        /* Build up a new full path including chroot directory */
        len = strlen(chroot) + strlen(PATH_SEPARATOR_STR) + strlen(file) + 1;
        chroot_file = alloc_buf_gc(len, &gc);
        buf_printf(&chroot_file, "%s%s%s", chroot, PATH_SEPARATOR_STR, file);
        ASSERT(chroot_file.len > 0);

        ret = check_file_access(type, BSTR(&chroot_file), mode, opt);
        gc_free(&gc);
    }
    else
    {
        /* No chroot in play, just call core file check function */
        ret = check_file_access(type, file, mode, opt);
    }
    return ret;
}