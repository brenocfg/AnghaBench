#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64 ;
typedef  int uint32 ;
typedef  int uint16 ;
struct TYPE_12__ {scalar_t__ tiff_diroff; } ;
struct TYPE_11__ {scalar_t__ tiff_diroff; } ;
struct TYPE_13__ {TYPE_2__ big; TYPE_1__ classic; } ;
struct TYPE_14__ {scalar_t__ tif_diroff; int tif_flags; char const* tif_name; int /*<<< orphan*/  tif_clientdata; TYPE_3__ tif_header; } ;
typedef  TYPE_4__ TIFF ;

/* Variables and functions */
 int /*<<< orphan*/  ReadOK (TYPE_4__*,int*,int) ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  SeekOK (TYPE_4__*,int) ; 
 int /*<<< orphan*/  TIFFErrorExt (int /*<<< orphan*/ ,char const*,char*) ; 
 int /*<<< orphan*/  TIFFSeekFile (TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TIFFSwabLong (int*) ; 
 int /*<<< orphan*/  TIFFSwabLong8 (int*) ; 
 int /*<<< orphan*/  TIFFSwabShort (int*) ; 
 int TIFFWriteDirectory (TYPE_4__*) ; 
 int TIFF_BIGTIFF ; 
 int TIFF_SWAB ; 
 int /*<<< orphan*/  WriteOK (TYPE_4__*,int*,int) ; 

int
TIFFRewriteDirectory( TIFF *tif )
{
	static const char module[] = "TIFFRewriteDirectory";

	/* We don't need to do anything special if it hasn't been written. */
	if( tif->tif_diroff == 0 )
		return TIFFWriteDirectory( tif );

	/*
	 * Find and zero the pointer to this directory, so that TIFFLinkDirectory
	 * will cause it to be added after this directories current pre-link.
	 */

	if (!(tif->tif_flags&TIFF_BIGTIFF))
	{
		if (tif->tif_header.classic.tiff_diroff == tif->tif_diroff)
		{
			tif->tif_header.classic.tiff_diroff = 0;
			tif->tif_diroff = 0;

			TIFFSeekFile(tif,4,SEEK_SET);
			if (!WriteOK(tif, &(tif->tif_header.classic.tiff_diroff),4))
			{
				TIFFErrorExt(tif->tif_clientdata, tif->tif_name,
				    "Error updating TIFF header");
				return (0);
			}
		}
		else
		{
			uint32 nextdir;
			nextdir = tif->tif_header.classic.tiff_diroff;
			while(1) {
				uint16 dircount;
				uint32 nextnextdir;

				if (!SeekOK(tif, nextdir) ||
				    !ReadOK(tif, &dircount, 2)) {
					TIFFErrorExt(tif->tif_clientdata, module,
					     "Error fetching directory count");
					return (0);
				}
				if (tif->tif_flags & TIFF_SWAB)
					TIFFSwabShort(&dircount);
				(void) TIFFSeekFile(tif,
				    nextdir+2+dircount*12, SEEK_SET);
				if (!ReadOK(tif, &nextnextdir, 4)) {
					TIFFErrorExt(tif->tif_clientdata, module,
					     "Error fetching directory link");
					return (0);
				}
				if (tif->tif_flags & TIFF_SWAB)
					TIFFSwabLong(&nextnextdir);
				if (nextnextdir==tif->tif_diroff)
				{
					uint32 m;
					m=0;
					(void) TIFFSeekFile(tif,
					    nextdir+2+dircount*12, SEEK_SET);
					if (!WriteOK(tif, &m, 4)) {
						TIFFErrorExt(tif->tif_clientdata, module,
						     "Error writing directory link");
						return (0);
					}
					tif->tif_diroff=0;
					break;
				}
				nextdir=nextnextdir;
			}
		}
	}
	else
	{
		if (tif->tif_header.big.tiff_diroff == tif->tif_diroff)
		{
			tif->tif_header.big.tiff_diroff = 0;
			tif->tif_diroff = 0;

			TIFFSeekFile(tif,8,SEEK_SET);
			if (!WriteOK(tif, &(tif->tif_header.big.tiff_diroff),8))
			{
				TIFFErrorExt(tif->tif_clientdata, tif->tif_name,
				    "Error updating TIFF header");
				return (0);
			}
		}
		else
		{
			uint64 nextdir;
			nextdir = tif->tif_header.big.tiff_diroff;
			while(1) {
				uint64 dircount64;
				uint16 dircount;
				uint64 nextnextdir;

				if (!SeekOK(tif, nextdir) ||
				    !ReadOK(tif, &dircount64, 8)) {
					TIFFErrorExt(tif->tif_clientdata, module,
					     "Error fetching directory count");
					return (0);
				}
				if (tif->tif_flags & TIFF_SWAB)
					TIFFSwabLong8(&dircount64);
				if (dircount64>0xFFFF)
				{
					TIFFErrorExt(tif->tif_clientdata, module,
					     "Sanity check on tag count failed, likely corrupt TIFF");
					return (0);
				}
				dircount=(uint16)dircount64;
				(void) TIFFSeekFile(tif,
				    nextdir+8+dircount*20, SEEK_SET);
				if (!ReadOK(tif, &nextnextdir, 8)) {
					TIFFErrorExt(tif->tif_clientdata, module,
					     "Error fetching directory link");
					return (0);
				}
				if (tif->tif_flags & TIFF_SWAB)
					TIFFSwabLong8(&nextnextdir);
				if (nextnextdir==tif->tif_diroff)
				{
					uint64 m;
					m=0;
					(void) TIFFSeekFile(tif,
					    nextdir+8+dircount*20, SEEK_SET);
					if (!WriteOK(tif, &m, 8)) {
						TIFFErrorExt(tif->tif_clientdata, module,
						     "Error writing directory link");
						return (0);
					}
					tif->tif_diroff=0;
					break;
				}
				nextdir=nextnextdir;
			}
		}
	}

	/*
	 * Now use TIFFWriteDirectory() normally.
	 */

	return TIFFWriteDirectory( tif );
}