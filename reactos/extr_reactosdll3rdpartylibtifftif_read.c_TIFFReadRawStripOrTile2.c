#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32 ;
typedef  int /*<<< orphan*/  tmsize_t ;
struct TYPE_7__ {int /*<<< orphan*/ * td_stripoffset; } ;
struct TYPE_8__ {int tif_flags; scalar_t__ tif_col; scalar_t__ tif_row; int /*<<< orphan*/  tif_clientdata; TYPE_1__ tif_dir; } ;
typedef  TYPE_1__ TIFFDirectory ;
typedef  TYPE_2__ TIFF ;

/* Variables and functions */
 int /*<<< orphan*/  SeekOK (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TIFFErrorExt (int /*<<< orphan*/ ,char const*,char*,unsigned long,unsigned long,...) ; 
 int /*<<< orphan*/  TIFFReadAndRealloc (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,size_t,char const*) ; 
 int TIFF_NOREADRAW ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  isMapped (TYPE_2__*) ; 

__attribute__((used)) static tmsize_t
TIFFReadRawStripOrTile2(TIFF* tif, uint32 strip_or_tile, int is_strip,
                        tmsize_t size, const char* module)
{
        TIFFDirectory *td = &tif->tif_dir;

        assert( !isMapped(tif) );
        assert((tif->tif_flags&TIFF_NOREADRAW)==0);

        if (!SeekOK(tif, td->td_stripoffset[strip_or_tile])) {
            if( is_strip )
            {
                TIFFErrorExt(tif->tif_clientdata, module,
                    "Seek error at scanline %lu, strip %lu",
                    (unsigned long) tif->tif_row,
                    (unsigned long) strip_or_tile);
            }
            else
            {
                TIFFErrorExt(tif->tif_clientdata, module,
                    "Seek error at row %lu, col %lu, tile %lu",
                    (unsigned long) tif->tif_row,
                    (unsigned long) tif->tif_col,
                    (unsigned long) strip_or_tile);
            }
            return ((tmsize_t)(-1));
        }

        if( !TIFFReadAndRealloc( tif, size, 0, is_strip,
                                 strip_or_tile, module ) )
        {
            return ((tmsize_t)(-1));
        }

        return (size);
}