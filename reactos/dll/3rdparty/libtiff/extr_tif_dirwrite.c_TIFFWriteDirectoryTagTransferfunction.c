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
typedef  int uint16 ;
struct TYPE_5__ {int td_bitspersample; int td_samplesperpixel; int td_extrasamples; int /*<<< orphan*/ * td_transferfunction; } ;
struct TYPE_6__ {TYPE_1__ tif_dir; int /*<<< orphan*/  tif_clientdata; } ;
typedef  int /*<<< orphan*/  TIFFDirEntry ;
typedef  TYPE_2__ TIFF ;

/* Variables and functions */
 int /*<<< orphan*/  TIFFErrorExt (int /*<<< orphan*/ ,char const*,char*) ; 
 int /*<<< orphan*/  TIFFTAG_TRANSFERFUNCTION ; 
 int TIFFWriteDirectoryTagCheckedShortArray (TYPE_2__*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  _TIFFfree (int*) ; 
 int* _TIFFmalloc (int) ; 
 int /*<<< orphan*/  _TIFFmemcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  _TIFFmemcpy (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
TIFFWriteDirectoryTagTransferfunction(TIFF* tif, uint32* ndir, TIFFDirEntry* dir)
{
	static const char module[] = "TIFFWriteDirectoryTagTransferfunction";
	uint32 m;
	uint16 n;
	uint16* o;
	int p;
	if (dir==NULL)
	{
		(*ndir)++;
		return(1);
	}
	m=(1<<tif->tif_dir.td_bitspersample);
	n=tif->tif_dir.td_samplesperpixel-tif->tif_dir.td_extrasamples;
	/*
	 * Check if the table can be written as a single column,
	 * or if it must be written as 3 columns.  Note that we
	 * write a 3-column tag if there are 2 samples/pixel and
	 * a single column of data won't suffice--hmm.
	 */
	if (n>3)
		n=3;
	if (n==3)
	{
		if (!_TIFFmemcmp(tif->tif_dir.td_transferfunction[0],tif->tif_dir.td_transferfunction[2],m*sizeof(uint16)))
			n=2;
	}
	if (n==2)
	{
		if (!_TIFFmemcmp(tif->tif_dir.td_transferfunction[0],tif->tif_dir.td_transferfunction[1],m*sizeof(uint16)))
			n=1;
	}
	if (n==0)
		n=1;
	o=_TIFFmalloc(n*m*sizeof(uint16));
	if (o==NULL)
	{
		TIFFErrorExt(tif->tif_clientdata,module,"Out of memory");
		return(0);
	}
	_TIFFmemcpy(&o[0],tif->tif_dir.td_transferfunction[0],m*sizeof(uint16));
	if (n>1)
		_TIFFmemcpy(&o[m],tif->tif_dir.td_transferfunction[1],m*sizeof(uint16));
	if (n>2)
		_TIFFmemcpy(&o[2*m],tif->tif_dir.td_transferfunction[2],m*sizeof(uint16));
	p=TIFFWriteDirectoryTagCheckedShortArray(tif,ndir,dir,TIFFTAG_TRANSFERFUNCTION,n*m,o);
	_TIFFfree(o);
	return(p);
}