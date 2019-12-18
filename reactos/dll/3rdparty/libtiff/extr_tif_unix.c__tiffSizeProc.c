#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64 ;
typedef  int /*<<< orphan*/  thandle_t ;
struct TYPE_4__ {int /*<<< orphan*/  fd; int /*<<< orphan*/  h; } ;
typedef  TYPE_1__ fd_as_handle_union_t ;
struct TYPE_5__ {scalar_t__ st_size; } ;
typedef  TYPE_2__ _TIFF_stat_s ;

/* Variables and functions */
 scalar_t__ _TIFF_fstat_f (int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static uint64
_tiffSizeProc(thandle_t fd)
{
	_TIFF_stat_s sb;
	fd_as_handle_union_t fdh;
	fdh.h = fd;
	if (_TIFF_fstat_f(fdh.fd,&sb)<0)
		return(0);
	else
		return((uint64)sb.st_size);
}