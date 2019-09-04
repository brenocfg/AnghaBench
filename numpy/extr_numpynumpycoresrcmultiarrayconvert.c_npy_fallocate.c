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
typedef  int /*<<< orphan*/  npy_intp ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */

__attribute__((used)) static int
npy_fallocate(npy_intp nbytes, FILE * fp)
{
    /*
     * unknown behavior on non-linux so don't try it
     * we don't want explicit zeroing to happen
     */
#if defined(HAVE_FALLOCATE) && defined(__linux__)
    int r;
    /* small files not worth the system call */
    if (nbytes < 16 * 1024 * 1024) {
        return 0;
    }

    /* btrfs can take a while to allocate making release worthwhile */
    NPY_BEGIN_ALLOW_THREADS;
    /*
     * flush in case there might be some unexpected interactions between the
     * fallocate call and unwritten data in the descriptor
     */
    fflush(fp);
    /*
     * the flag "1" (=FALLOC_FL_KEEP_SIZE) is needed for the case of files
     * opened in append mode (issue #8329)
     */
    r = fallocate(fileno(fp), 1, npy_ftell(fp), nbytes);
    NPY_END_ALLOW_THREADS;

    /*
     * early exit on no space, other errors will also get found during fwrite
     */
    if (r == -1 && errno == ENOSPC) {
        PyErr_Format(PyExc_IOError, "Not enough free space to write "
                     "%"NPY_INTP_FMT" bytes", nbytes);
        return -1;
    }
#endif
    return 0;
}