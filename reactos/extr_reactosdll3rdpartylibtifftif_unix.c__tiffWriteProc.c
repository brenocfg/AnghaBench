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
typedef  scalar_t__ tmsize_t ;
typedef  int /*<<< orphan*/  thandle_t ;
struct TYPE_2__ {int /*<<< orphan*/  fd; int /*<<< orphan*/  h; } ;
typedef  TYPE_1__ fd_as_handle_union_t ;
typedef  int /*<<< orphan*/  TIFFIOSize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 size_t TIFF_IO_MAX ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ write (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static tmsize_t
_tiffWriteProc(thandle_t fd, void* buf, tmsize_t size)
{
	fd_as_handle_union_t fdh;
	const size_t bytes_total = (size_t) size;
        size_t bytes_written;
        tmsize_t count = -1;
	if ((tmsize_t) bytes_total != size)
	{
		errno=EINVAL;
		return (tmsize_t) -1;
	}
	fdh.h = fd;
        for (bytes_written=0; bytes_written < bytes_total; bytes_written+=count)
        {
                const char *buf_offset = (char *) buf+bytes_written;
                size_t io_size = bytes_total-bytes_written;
                if (io_size > TIFF_IO_MAX)
                        io_size = TIFF_IO_MAX;
                count=write(fdh.fd, buf_offset, (TIFFIOSize_t) io_size);
                if (count <= 0)
                        break;
        }
        if (count < 0)
                return (tmsize_t)-1;
        return (tmsize_t) bytes_written;
	/* return ((tmsize_t) write(fdh.fd, buf, bytes_total)); */
}