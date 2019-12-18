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
typedef  int uint32 ;
typedef  int /*<<< orphan*/  uint16 ;
struct TYPE_5__ {int td_bitspersample; int /*<<< orphan*/ * td_colormap; } ;
struct TYPE_6__ {TYPE_1__ tif_dir; int /*<<< orphan*/  tif_clientdata; } ;
typedef  int /*<<< orphan*/  TIFFDirEntry ;
typedef  TYPE_2__ TIFF ;

/* Variables and functions */
 int /*<<< orphan*/  TIFFErrorExt (int /*<<< orphan*/ ,char const*,char*) ; 
 int /*<<< orphan*/  TIFFTAG_COLORMAP ; 
 int TIFFWriteDirectoryTagCheckedShortArray (TYPE_2__*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _TIFFfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * _TIFFmalloc (int) ; 
 int /*<<< orphan*/  _TIFFmemcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
TIFFWriteDirectoryTagColormap(TIFF* tif, uint32* ndir, TIFFDirEntry* dir)
{
	static const char module[] = "TIFFWriteDirectoryTagColormap";
	uint32 m;
	uint16* n;
	int o;
	if (dir==NULL)
	{
		(*ndir)++;
		return(1);
	}
	m=(1<<tif->tif_dir.td_bitspersample);
	n=_TIFFmalloc(3*m*sizeof(uint16));
	if (n==NULL)
	{
		TIFFErrorExt(tif->tif_clientdata,module,"Out of memory");
		return(0);
	}
	_TIFFmemcpy(&n[0],tif->tif_dir.td_colormap[0],m*sizeof(uint16));
	_TIFFmemcpy(&n[m],tif->tif_dir.td_colormap[1],m*sizeof(uint16));
	_TIFFmemcpy(&n[2*m],tif->tif_dir.td_colormap[2],m*sizeof(uint16));
	o=TIFFWriteDirectoryTagCheckedShortArray(tif,ndir,dir,TIFFTAG_COLORMAP,3*m,n);
	_TIFFfree(n);
	return(o);
}