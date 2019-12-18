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
typedef  size_t ssize_t ;
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  AT_EXECFN ; 
 int /*<<< orphan*/  EACCES ; 
 int /*<<< orphan*/  EOVERFLOW ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ getauxval (int /*<<< orphan*/ ) ; 
 scalar_t__ getpid () ; 
 int /*<<< orphan*/  memcpy (void*,char const*,size_t) ; 
 size_t readlink (char*,void*,size_t) ; 
 size_t strlen (char const*) ; 

int proc_pidpath(pid_t pid, void *buffer, size_t buffersize)
{
    ssize_t path_len;

    if (getpid() != pid) {
        errno = EACCES;

        return -1;
    }

#if defined(HAVE_GETAUXVAL)
    const char *execfn = (const char *)getauxval(AT_EXECFN);

    if (execfn) {
        size_t len = strlen(execfn);

        if (len + 1 < buffersize) {
            memcpy(buffer, execfn, len + 1);

            return 0;
        }
    }
#endif

    path_len = readlink("/proc/self/exe", buffer, buffersize);
    if (path_len < 0)
        return -1;

    if (path_len < (ssize_t)buffersize) {
        ((char *)buffer)[path_len] = '\0';

        return 0;
    }

    errno = EOVERFLOW;
    return -1;
}