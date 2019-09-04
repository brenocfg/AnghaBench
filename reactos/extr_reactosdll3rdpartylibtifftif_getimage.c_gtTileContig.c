#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32 ;
typedef  scalar_t__ tmsize_t ;
typedef  int /*<<< orphan*/  (* tileContigRoutine ) (TYPE_2__*,int*,int,int,int,int,int,int,unsigned char*) ;
typedef  int int32 ;
struct TYPE_15__ {int /*<<< orphan*/  tif_clientdata; } ;
struct TYPE_13__ {int /*<<< orphan*/  (* contig ) (TYPE_2__*,int*,int,int,int,int,int,int,unsigned char*) ;} ;
struct TYPE_14__ {int col_offset; int row_offset; scalar_t__ samplesperpixel; scalar_t__ stoponerr; TYPE_1__ put; TYPE_4__* tif; } ;
typedef  TYPE_2__ TIFFRGBAImage ;
typedef  TYPE_4__ TIFF ;

/* Variables and functions */
 int FLIP_HORIZONTALLY ; 
 int FLIP_VERTICALLY ; 
 int /*<<< orphan*/  TIFFErrorExt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  TIFFFileName (TYPE_4__*) ; 
 int /*<<< orphan*/  TIFFGetField (TYPE_4__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  TIFFTAG_TILELENGTH ; 
 int /*<<< orphan*/  TIFFTAG_TILEWIDTH ; 
 int TIFFTileRowSize (TYPE_4__*) ; 
 scalar_t__ TIFFTileSize (TYPE_4__*) ; 
 scalar_t__ _TIFFReadTileAndAllocBuffer (TYPE_4__*,void**,scalar_t__,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _TIFFfree (unsigned char*) ; 
 int setorientation (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int*,int,int,int,int,int,int,unsigned char*) ; 

__attribute__((used)) static int
gtTileContig(TIFFRGBAImage* img, uint32* raster, uint32 w, uint32 h)
{
    TIFF* tif = img->tif;
    tileContigRoutine put = img->put.contig;
    uint32 col, row, y, rowstoread;
    tmsize_t pos;
    uint32 tw, th;
    unsigned char* buf = NULL;
    int32 fromskew, toskew;
    uint32 nrow;
    int ret = 1, flip;
    uint32 this_tw, tocol;
    int32 this_toskew, leftmost_toskew;
    int32 leftmost_fromskew;
    uint32 leftmost_tw;
    tmsize_t bufsize;

    bufsize = TIFFTileSize(tif);
    if (bufsize == 0) {
        TIFFErrorExt(tif->tif_clientdata, TIFFFileName(tif), "%s", "No space for tile buffer");
        return (0);
    }

    TIFFGetField(tif, TIFFTAG_TILEWIDTH, &tw);
    TIFFGetField(tif, TIFFTAG_TILELENGTH, &th);

    flip = setorientation(img);
    if (flip & FLIP_VERTICALLY) {
	    y = h - 1;
	    toskew = -(int32)(tw + w);
    }
    else {
	    y = 0;
	    toskew = -(int32)(tw - w);
    }
     
    /*
     *	Leftmost tile is clipped on left side if col_offset > 0.
     */
    leftmost_fromskew = img->col_offset % tw;
    leftmost_tw = tw - leftmost_fromskew;
    leftmost_toskew = toskew + leftmost_fromskew;
    for (row = 0; ret != 0 && row < h; row += nrow)
    {
        rowstoread = th - (row + img->row_offset) % th;
    	nrow = (row + rowstoread > h ? h - row : rowstoread);
	fromskew = leftmost_fromskew;
	this_tw = leftmost_tw;
	this_toskew = leftmost_toskew;
	tocol = 0;
	col = img->col_offset;
	while (tocol < w)
        {
	    if (_TIFFReadTileAndAllocBuffer(tif, (void**) &buf, bufsize, col,
			     row+img->row_offset, 0, 0)==(tmsize_t)(-1) &&
                (buf == NULL || img->stoponerr))
            {
                ret = 0;
                break;
            }
            pos = ((row+img->row_offset) % th) * TIFFTileRowSize(tif) + \
		   ((tmsize_t) fromskew * img->samplesperpixel);
	    if (tocol + this_tw > w) 
	    {
		/*
		 * Rightmost tile is clipped on right side.
		 */
		fromskew = tw - (w - tocol);
		this_tw = tw - fromskew;
		this_toskew = toskew + fromskew;
	    }
	    (*put)(img, raster+y*w+tocol, tocol, y, this_tw, nrow, fromskew, this_toskew, buf + pos);
	    tocol += this_tw;
	    col += this_tw;
	    /*
	     * After the leftmost tile, tiles are no longer clipped on left side.
	     */
	    fromskew = 0;
	    this_tw = tw;
	    this_toskew = toskew;
	}

        y += ((flip & FLIP_VERTICALLY) ? -(int32) nrow : (int32) nrow);
    }
    _TIFFfree(buf);

    if (flip & FLIP_HORIZONTALLY) {
	    uint32 line;

	    for (line = 0; line < h; line++) {
		    uint32 *left = raster + (line * w);
		    uint32 *right = left + w - 1;
		    
		    while ( left < right ) {
			    uint32 temp = *left;
			    *left = *right;
			    *right = temp;
			    left++;
				right--;
		    }
	    }
    }

    return (ret);
}