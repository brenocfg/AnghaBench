#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int fd; int /*<<< orphan*/  h; } ;
typedef  TYPE_1__ fd_as_handle_union_t ;
struct TYPE_6__ {int tif_fd; } ;
typedef  TYPE_2__ TIFF ;

/* Variables and functions */
 TYPE_2__* TIFFClientOpen (char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _tiffCloseProc ; 
 int /*<<< orphan*/  _tiffMapProc ; 
 int /*<<< orphan*/  _tiffReadProc ; 
 int /*<<< orphan*/  _tiffSeekProc ; 
 int /*<<< orphan*/  _tiffSizeProc ; 
 int /*<<< orphan*/  _tiffUnmapProc ; 
 int /*<<< orphan*/  _tiffWriteProc ; 

TIFF*
TIFFFdOpen(int fd, const char* name, const char* mode)
{
	TIFF* tif;

	fd_as_handle_union_t fdh;
	fdh.fd = fd;
	tif = TIFFClientOpen(name, mode,
	    fdh.h,
	    _tiffReadProc, _tiffWriteProc,
	    _tiffSeekProc, _tiffCloseProc, _tiffSizeProc,
	    _tiffMapProc, _tiffUnmapProc);
	if (tif)
		tif->tif_fd = fd;
	return (tif);
}