#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32 ;
typedef  int uint16 ;
typedef  int tmsize_t ;
typedef  int /*<<< orphan*/  (* tileContigRoutine ) (TYPE_2__*,int*,int /*<<< orphan*/ ,int,int,int,int,int,unsigned char*) ;
typedef  int int32 ;
struct TYPE_16__ {int /*<<< orphan*/  tif_clientdata; } ;
struct TYPE_14__ {int /*<<< orphan*/  (* contig ) (TYPE_2__*,int*,int /*<<< orphan*/ ,int,int,int,int,int,unsigned char*) ;} ;
struct TYPE_15__ {int width; int row_offset; int samplesperpixel; scalar_t__ col_offset; scalar_t__ stoponerr; TYPE_1__ put; TYPE_4__* tif; } ;
typedef  TYPE_2__ TIFFRGBAImage ;
typedef  TYPE_4__ TIFF ;

/* Variables and functions */
 int FLIP_HORIZONTALLY ; 
 int FLIP_VERTICALLY ; 
 int /*<<< orphan*/  TIFFComputeStrip (TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TIFFErrorExt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TIFFFileName (TYPE_4__*) ; 
 int /*<<< orphan*/  TIFFGetFieldDefaulted (TYPE_4__*,int /*<<< orphan*/ ,int*,...) ; 
 int TIFFScanlineSize (TYPE_4__*) ; 
 int TIFFStripSize (TYPE_4__*) ; 
 int /*<<< orphan*/  TIFFTAG_ROWSPERSTRIP ; 
 int /*<<< orphan*/  TIFFTAG_YCBCRSUBSAMPLING ; 
 int _TIFFReadEncodedStripAndAllocBuffer (TYPE_4__*,int /*<<< orphan*/ ,void**,int,int) ; 
 int /*<<< orphan*/  _TIFFfree (unsigned char*) ; 
 int setorientation (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int*,int /*<<< orphan*/ ,int,int,int,int,int,unsigned char*) ; 

__attribute__((used)) static int
gtStripContig(TIFFRGBAImage* img, uint32* raster, uint32 w, uint32 h)
{
	TIFF* tif = img->tif;
	tileContigRoutine put = img->put.contig;
	uint32 row, y, nrow, nrowsub, rowstoread;
	tmsize_t pos;
	unsigned char* buf = NULL;
	uint32 rowsperstrip;
	uint16 subsamplinghor,subsamplingver;
	uint32 imagewidth = img->width;
	tmsize_t scanline;
	int32 fromskew, toskew;
	int ret = 1, flip;
        tmsize_t maxstripsize;

	TIFFGetFieldDefaulted(tif, TIFFTAG_YCBCRSUBSAMPLING, &subsamplinghor, &subsamplingver);
	if( subsamplingver == 0 ) {
		TIFFErrorExt(tif->tif_clientdata, TIFFFileName(tif), "Invalid vertical YCbCr subsampling");
		return (0);
	}
	
	maxstripsize = TIFFStripSize(tif);

	flip = setorientation(img);
	if (flip & FLIP_VERTICALLY) {
		y = h - 1;
		toskew = -(int32)(w + w);
	} else {
		y = 0;
		toskew = -(int32)(w - w);
	}

	TIFFGetFieldDefaulted(tif, TIFFTAG_ROWSPERSTRIP, &rowsperstrip);

	scanline = TIFFScanlineSize(tif);
	fromskew = (w < imagewidth ? imagewidth - w : 0);
	for (row = 0; row < h; row += nrow)
	{
		rowstoread = rowsperstrip - (row + img->row_offset) % rowsperstrip;
		nrow = (row + rowstoread > h ? h - row : rowstoread);
		nrowsub = nrow;
		if ((nrowsub%subsamplingver)!=0)
			nrowsub+=subsamplingver-nrowsub%subsamplingver;
		if (_TIFFReadEncodedStripAndAllocBuffer(tif,
		    TIFFComputeStrip(tif,row+img->row_offset, 0),
		    (void**)(&buf),
                    maxstripsize,
		    ((row + img->row_offset)%rowsperstrip + nrowsub) * scanline)==(tmsize_t)(-1)
		    && (buf == NULL || img->stoponerr))
		{
			ret = 0;
			break;
		}

		pos = ((row + img->row_offset) % rowsperstrip) * scanline + \
			((tmsize_t) img->col_offset * img->samplesperpixel);
		(*put)(img, raster+y*w, 0, y, w, nrow, fromskew, toskew, buf + pos);
		y += ((flip & FLIP_VERTICALLY) ? -(int32) nrow : (int32) nrow);
	}

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

	_TIFFfree(buf);
	return (ret);
}