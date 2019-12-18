#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  thandle_t ;
struct TYPE_4__ {int tif_fd; } ;
typedef  TYPE_1__ TIFF ;

/* Variables and functions */
 TYPE_1__* TIFFClientOpen (char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _tiffCloseProc ; 
 int /*<<< orphan*/  _tiffDummyMapProc ; 
 int /*<<< orphan*/  _tiffDummyUnmapProc ; 
 int /*<<< orphan*/  _tiffMapProc ; 
 int /*<<< orphan*/  _tiffReadProc ; 
 int /*<<< orphan*/  _tiffSeekProc ; 
 int /*<<< orphan*/  _tiffSizeProc ; 
 int /*<<< orphan*/  _tiffUnmapProc ; 
 int /*<<< orphan*/  _tiffWriteProc ; 

TIFF*
TIFFFdOpen(int ifd, const char* name, const char* mode)
{
	TIFF* tif;
	int fSuppressMap;
	int m;
	fSuppressMap=0;
	for (m=0; mode[m]!=0; m++)
	{
		if (mode[m]=='u')
		{
			fSuppressMap=1;
			break;
		}
	}
	tif = TIFFClientOpen(name, mode, (thandle_t)ifd, /* FIXME: WIN64 cast to pointer warning */
			_tiffReadProc, _tiffWriteProc,
			_tiffSeekProc, _tiffCloseProc, _tiffSizeProc,
			fSuppressMap ? _tiffDummyMapProc : _tiffMapProc,
			fSuppressMap ? _tiffDummyUnmapProc : _tiffUnmapProc);
	if (tif)
		tif->tif_fd = ifd;
	return (tif);
}