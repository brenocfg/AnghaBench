#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8 ;
typedef  scalar_t__ uint32 ;
typedef  int /*<<< orphan*/  uint16 ;
struct TYPE_7__ {int (* tif_decoderow ) (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  tif_scanlinesize; int /*<<< orphan*/  (* tif_postdecode ) (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;scalar_t__ tif_row; } ;
typedef  TYPE_1__ TIFF ;

/* Variables and functions */
 int /*<<< orphan*/  TIFFCheckRead (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int TIFFSeek (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
TIFFReadScanline(TIFF* tif, void* buf, uint32 row, uint16 sample)
{
	int e;

	if (!TIFFCheckRead(tif, 0))
		return (-1);
	if( (e = TIFFSeek(tif, row, sample)) != 0) {
		/*
		 * Decompress desired row into user buffer.
		 */
		e = (*tif->tif_decoderow)
		    (tif, (uint8*) buf, tif->tif_scanlinesize, sample);  

		/* we are now poised at the beginning of the next row */
		tif->tif_row = row + 1;

		if (e)
			(*tif->tif_postdecode)(tif, (uint8*) buf,
			    tif->tif_scanlinesize);  
	}
	return (e > 0 ? 1 : -1);
}