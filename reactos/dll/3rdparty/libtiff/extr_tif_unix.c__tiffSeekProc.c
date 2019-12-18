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
typedef  scalar_t__ uint64 ;
typedef  int /*<<< orphan*/  thandle_t ;
struct TYPE_2__ {int /*<<< orphan*/  fd; int /*<<< orphan*/  h; } ;
typedef  TYPE_1__ fd_as_handle_union_t ;
typedef  scalar_t__ _TIFF_off_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 scalar_t__ _TIFF_lseek_f (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  errno ; 

__attribute__((used)) static uint64
_tiffSeekProc(thandle_t fd, uint64 off, int whence)
{
	fd_as_handle_union_t fdh;
	_TIFF_off_t off_io = (_TIFF_off_t) off;
	if ((uint64) off_io != off)
	{
		errno=EINVAL;
		return (uint64) -1; /* this is really gross */
	}
	fdh.h = fd;
	return((uint64)_TIFF_lseek_f(fdh.fd,off_io,whence));
}