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
typedef  scalar_t__ uint64 ;
struct TYPE_5__ {scalar_t__ td_tilelength; scalar_t__ td_tilewidth; scalar_t__ td_bitspersample; scalar_t__ td_planarconfig; scalar_t__ td_samplesperpixel; } ;
struct TYPE_6__ {int /*<<< orphan*/  tif_clientdata; TYPE_1__ tif_dir; } ;
typedef  TYPE_1__ TIFFDirectory ;
typedef  TYPE_2__ TIFF ;

/* Variables and functions */
 scalar_t__ PLANARCONFIG_CONTIG ; 
 int /*<<< orphan*/  TIFFErrorExt (int /*<<< orphan*/ ,char const*,char*) ; 
 scalar_t__ TIFFhowmany8_64 (scalar_t__) ; 
 scalar_t__ _TIFFMultiply64 (TYPE_2__*,scalar_t__,scalar_t__,char*) ; 

uint64
TIFFTileRowSize64(TIFF* tif)
{
        static const char module[] = "TIFFTileRowSize64";
	TIFFDirectory *td = &tif->tif_dir;
	uint64 rowsize;
	uint64 tilerowsize;

	if (td->td_tilelength == 0)
        {
                TIFFErrorExt(tif->tif_clientdata,module,"Tile length is zero");
                return 0;
        }
        if (td->td_tilewidth == 0)
        {
                TIFFErrorExt(tif->tif_clientdata,module,"Tile width is zero");
		return (0);
        }
	rowsize = _TIFFMultiply64(tif, td->td_bitspersample, td->td_tilewidth,
	    "TIFFTileRowSize");
	if (td->td_planarconfig == PLANARCONFIG_CONTIG)
        {
                if (td->td_samplesperpixel == 0)
                {
                        TIFFErrorExt(tif->tif_clientdata,module,"Samples per pixel is zero");
                        return 0;
                }
		rowsize = _TIFFMultiply64(tif, rowsize, td->td_samplesperpixel,
		    "TIFFTileRowSize");
        }
        tilerowsize=TIFFhowmany8_64(rowsize);
        if (tilerowsize == 0)
        {
                TIFFErrorExt(tif->tif_clientdata,module,"Computed tile row size is zero");
                return 0;
        }
	return (tilerowsize);
}