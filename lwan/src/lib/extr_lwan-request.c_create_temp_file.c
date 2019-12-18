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
typedef  int /*<<< orphan*/  template ;
typedef  int mode_t ;

/* Variables and functions */
 int ENOENT ; 
 int EOVERFLOW ; 
 scalar_t__ LIKELY (int) ; 
 int O_CLOEXEC ; 
 int O_CREAT ; 
 int O_EXCL ; 
 int O_NOATIME ; 
 int O_NOFOLLOW ; 
 int O_RDWR ; 
 int O_TMPFILE ; 
 int PATH_MAX ; 
 int S_IRUSR ; 
 int S_IWUSR ; 
 scalar_t__ UNLIKELY (int) ; 
 int mkostemp (char*,int) ; 
 int open (char*,int,int) ; 
 int snprintf (char*,int,char*,char*) ; 
 char* temp_dir ; 
 int umask_for_tmpfile (int) ; 
 int /*<<< orphan*/  unlink (char*) ; 

__attribute__((used)) static int create_temp_file(void)
{
    char template[PATH_MAX];
    mode_t prev_mask;
    int ret;

    if (UNLIKELY(!temp_dir))
        return -ENOENT;

#if defined(O_TMPFILE)
    int fd = open(temp_dir,
                  O_TMPFILE | O_CREAT | O_RDWR | O_EXCL | O_CLOEXEC |
                      O_NOFOLLOW | O_NOATIME,
                  S_IRUSR | S_IWUSR);
    if (LIKELY(fd >= 0))
        return fd;
#endif

    ret = snprintf(template, sizeof(template), "%s/lwanXXXXXX", temp_dir);
    if (UNLIKELY(ret < 0 || ret >= (int)sizeof(template)))
        return -EOVERFLOW;

    prev_mask = umask_for_tmpfile(S_IRUSR | S_IWUSR);
    ret = mkostemp(template, O_CLOEXEC);
    umask_for_tmpfile(prev_mask);

    if (LIKELY(ret >= 0))
        unlink(template);

    return ret;
}