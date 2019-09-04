#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64 ;
struct TYPE_9__ {int /*<<< orphan*/  td_nstrips; } ;
struct TYPE_10__ {scalar_t__ tif_mode; int tif_flags; TYPE_1__ tif_dir; } ;
typedef  TYPE_2__ TIFF ;

/* Variables and functions */
 scalar_t__ O_RDONLY ; 
 scalar_t__ O_RDWR ; 
 int /*<<< orphan*/  TIFFFlushData (TYPE_2__*) ; 
 scalar_t__ TIFFGetField (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ TIFFIsTiled (TYPE_2__*) ; 
 int /*<<< orphan*/  TIFFRewriteDirectory (TYPE_2__*) ; 
 int /*<<< orphan*/  TIFFTAG_STRIPBYTECOUNTS ; 
 int /*<<< orphan*/  TIFFTAG_STRIPOFFSETS ; 
 int /*<<< orphan*/  TIFFTAG_TILEBYTECOUNTS ; 
 int /*<<< orphan*/  TIFFTAG_TILEOFFSETS ; 
 int TIFF_BEENWRITING ; 
 int TIFF_DIRTYDIRECT ; 
 int TIFF_DIRTYSTRIP ; 
 int /*<<< orphan*/  TIFF_LONG8 ; 
 scalar_t__ _TIFFRewriteField (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
TIFFFlush(TIFF* tif)
{
    if( tif->tif_mode == O_RDONLY )
        return 1;

    if (!TIFFFlushData(tif))
        return (0);
                
    /* In update (r+) mode we try to detect the case where 
       only the strip/tile map has been altered, and we try to 
       rewrite only that portion of the directory without 
       making any other changes */
                
    if( (tif->tif_flags & TIFF_DIRTYSTRIP)
        && !(tif->tif_flags & TIFF_DIRTYDIRECT) 
        && tif->tif_mode == O_RDWR )
    {
        uint64  *offsets=NULL, *sizes=NULL;

        if( TIFFIsTiled(tif) )
        {
            if( TIFFGetField( tif, TIFFTAG_TILEOFFSETS, &offsets ) 
                && TIFFGetField( tif, TIFFTAG_TILEBYTECOUNTS, &sizes ) 
                && _TIFFRewriteField( tif, TIFFTAG_TILEOFFSETS, TIFF_LONG8, 
                                      tif->tif_dir.td_nstrips, offsets )
                && _TIFFRewriteField( tif, TIFFTAG_TILEBYTECOUNTS, TIFF_LONG8, 
                                      tif->tif_dir.td_nstrips, sizes ) )
            {
                tif->tif_flags &= ~TIFF_DIRTYSTRIP;
                tif->tif_flags &= ~TIFF_BEENWRITING;
                return 1;
            }
        }
        else
        {
            if( TIFFGetField( tif, TIFFTAG_STRIPOFFSETS, &offsets ) 
                && TIFFGetField( tif, TIFFTAG_STRIPBYTECOUNTS, &sizes ) 
                && _TIFFRewriteField( tif, TIFFTAG_STRIPOFFSETS, TIFF_LONG8, 
                                      tif->tif_dir.td_nstrips, offsets )
                && _TIFFRewriteField( tif, TIFFTAG_STRIPBYTECOUNTS, TIFF_LONG8, 
                                      tif->tif_dir.td_nstrips, sizes ) )
            {
                tif->tif_flags &= ~TIFF_DIRTYSTRIP;
                tif->tif_flags &= ~TIFF_BEENWRITING;
                return 1;
            }
        }
    }

    if ((tif->tif_flags & (TIFF_DIRTYDIRECT|TIFF_DIRTYSTRIP)) 
        && !TIFFRewriteDirectory(tif))
        return (0);

    return (1);
}