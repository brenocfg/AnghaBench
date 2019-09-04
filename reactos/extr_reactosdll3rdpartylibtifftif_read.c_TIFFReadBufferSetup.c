#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8 ;
typedef  int /*<<< orphan*/  uint64 ;
typedef  void* tmsize_t ;
struct TYPE_3__ {int tif_flags; scalar_t__ tif_rawdatasize; scalar_t__ tif_row; int /*<<< orphan*/  tif_clientdata; int /*<<< orphan*/ * tif_rawdata; } ;
typedef  TYPE_1__ TIFF ;

/* Variables and functions */
 int /*<<< orphan*/  TIFFErrorExt (int /*<<< orphan*/ ,char const*,char*,...) ; 
 int TIFF_BUFFERMMAP ; 
 int TIFF_MYBUFFER ; 
 int TIFF_NOREADRAW ; 
 scalar_t__ TIFFroundup_64 (int /*<<< orphan*/ ,int) ; 
 scalar_t__ _TIFFcalloc (int,scalar_t__) ; 
 int /*<<< orphan*/  _TIFFfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 

int
TIFFReadBufferSetup(TIFF* tif, void* bp, tmsize_t size)
{
	static const char module[] = "TIFFReadBufferSetup";

	assert((tif->tif_flags&TIFF_NOREADRAW)==0);
	tif->tif_flags &= ~TIFF_BUFFERMMAP;

	if (tif->tif_rawdata) {
		if (tif->tif_flags & TIFF_MYBUFFER)
			_TIFFfree(tif->tif_rawdata);
		tif->tif_rawdata = NULL;
		tif->tif_rawdatasize = 0;
	}
	if (bp) {
		tif->tif_rawdatasize = size;
		tif->tif_rawdata = (uint8*) bp;
		tif->tif_flags &= ~TIFF_MYBUFFER;
	} else {
		tif->tif_rawdatasize = (tmsize_t)TIFFroundup_64((uint64)size, 1024);
		if (tif->tif_rawdatasize==0) {
		    TIFFErrorExt(tif->tif_clientdata, module,
				 "Invalid buffer size");
		    return (0);
		}
		/* Initialize to zero to avoid uninitialized buffers in case of */
                /* short reads (http://bugzilla.maptools.org/show_bug.cgi?id=2651) */
		tif->tif_rawdata = (uint8*) _TIFFcalloc(1, tif->tif_rawdatasize);
		tif->tif_flags |= TIFF_MYBUFFER;
	}
	if (tif->tif_rawdata == NULL) {
		TIFFErrorExt(tif->tif_clientdata, module,
		    "No space for data buffer at scanline %lu",
		    (unsigned long) tif->tif_row);
		tif->tif_rawdatasize = 0;
		return (0);
	}
	return (1);
}