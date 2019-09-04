#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64 ;
typedef  scalar_t__ uint32 ;
typedef  scalar_t__ uint16 ;
struct TYPE_6__ {int td_nsubifd; int* td_subifd; } ;
struct TYPE_7__ {int tif_dataoff; int tif_flags; scalar_t__ tif_nsubifd; int tif_subifdoff; TYPE_1__ tif_dir; int /*<<< orphan*/  tif_clientdata; } ;
typedef  int /*<<< orphan*/  TIFFDirEntry ;
typedef  TYPE_2__ TIFF ;

/* Variables and functions */
 int /*<<< orphan*/  TIFFErrorExt (int /*<<< orphan*/ ,char const*,char*) ; 
 int /*<<< orphan*/  TIFFTAG_SUBIFD ; 
 int TIFFWriteDirectoryTagCheckedIfd8Array (TYPE_2__*,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int*) ; 
 int TIFFWriteDirectoryTagCheckedIfdArray (TYPE_2__*,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,scalar_t__*) ; 
 int TIFF_BIGTIFF ; 
 int TIFF_INSUBIFD ; 
 int /*<<< orphan*/  _TIFFfree (scalar_t__*) ; 
 scalar_t__* _TIFFmalloc (int) ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static int
TIFFWriteDirectoryTagSubifd(TIFF* tif, uint32* ndir, TIFFDirEntry* dir)
{
	static const char module[] = "TIFFWriteDirectoryTagSubifd";
	uint64 m;
	int n;
	if (tif->tif_dir.td_nsubifd==0)
		return(1);
	if (dir==NULL)
	{
		(*ndir)++;
		return(1);
	}
	m=tif->tif_dataoff;
	if (!(tif->tif_flags&TIFF_BIGTIFF))
	{
		uint32* o;
		uint64* pa;
		uint32* pb;
		uint16 p;
		o=_TIFFmalloc(tif->tif_dir.td_nsubifd*sizeof(uint32));
		if (o==NULL)
		{
			TIFFErrorExt(tif->tif_clientdata,module,"Out of memory");
			return(0);
		}
		pa=tif->tif_dir.td_subifd;
		pb=o;
		for (p=0; p < tif->tif_dir.td_nsubifd; p++)
		{
                        assert(pa != 0);

                        /* Could happen if an classicTIFF has a SubIFD of type LONG8 (which is illegal) */
                        if( *pa > 0xFFFFFFFFUL)
                        {
                            TIFFErrorExt(tif->tif_clientdata,module,"Illegal value for SubIFD tag");
                            _TIFFfree(o);
                            return(0);
                        }
			*pb++=(uint32)(*pa++);
		}
		n=TIFFWriteDirectoryTagCheckedIfdArray(tif,ndir,dir,TIFFTAG_SUBIFD,tif->tif_dir.td_nsubifd,o);
		_TIFFfree(o);
	}
	else
		n=TIFFWriteDirectoryTagCheckedIfd8Array(tif,ndir,dir,TIFFTAG_SUBIFD,tif->tif_dir.td_nsubifd,tif->tif_dir.td_subifd);
	if (!n)
		return(0);
	/*
	 * Total hack: if this directory includes a SubIFD
	 * tag then force the next <n> directories to be
	 * written as ``sub directories'' of this one.  This
	 * is used to write things like thumbnails and
	 * image masks that one wants to keep out of the
	 * normal directory linkage access mechanism.
	 */
	tif->tif_flags|=TIFF_INSUBIFD;
	tif->tif_nsubifd=tif->tif_dir.td_nsubifd;
	if (tif->tif_dir.td_nsubifd==1)
		tif->tif_subifdoff=0;
	else
		tif->tif_subifdoff=m;
	return(1);
}