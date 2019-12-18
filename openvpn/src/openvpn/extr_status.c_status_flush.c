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
struct status_output {scalar_t__ fd; int flags; int /*<<< orphan*/  read_buf; } ;
typedef  scalar_t__ off_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int M_ERRNO ; 
 int M_WARN ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int STATUS_OUTPUT_WRITE ; 
 scalar_t__ buf_defined (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  buf_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chsize (scalar_t__,long const) ; 
 scalar_t__ ftruncate (scalar_t__,scalar_t__ const) ; 
 scalar_t__ lseek (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg (int,char*) ; 

void
status_flush(struct status_output *so)
{
    if (so && so->fd >= 0 && (so->flags & STATUS_OUTPUT_WRITE))
    {
#if defined(HAVE_FTRUNCATE)
        {
            const off_t off = lseek(so->fd, (off_t)0, SEEK_CUR);
            if (ftruncate(so->fd, off) != 0)
            {
                msg(M_WARN | M_ERRNO, "Failed to truncate status file");
            }
        }
#elif defined(HAVE_CHSIZE)
        {
            const long off = (long) lseek(so->fd, (off_t)0, SEEK_CUR);
            chsize(so->fd, off);
        }
#else  /* if defined(HAVE_FTRUNCATE) */
#warning both ftruncate and chsize functions appear to be missing from this OS
#endif

        /* clear read buffer */
        if (buf_defined(&so->read_buf))
        {
            ASSERT(buf_init(&so->read_buf, 0));
        }
    }
}