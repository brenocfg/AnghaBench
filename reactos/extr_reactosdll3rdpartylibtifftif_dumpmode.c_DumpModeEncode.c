#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8 ;
typedef  int /*<<< orphan*/  uint16 ;
typedef  scalar_t__ tmsize_t ;
struct TYPE_4__ {scalar_t__ tif_rawcc; scalar_t__ tif_rawdatasize; int /*<<< orphan*/ * tif_rawcp; } ;
typedef  TYPE_1__ TIFF ;

/* Variables and functions */
 int /*<<< orphan*/  TIFFFlushData1 (TYPE_1__*) ; 
 int /*<<< orphan*/  _TIFFmemcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static int
DumpModeEncode(TIFF* tif, uint8* pp, tmsize_t cc, uint16 s)
{
	(void) s;
	while (cc > 0) {
		tmsize_t n;

		n = cc;
		if (tif->tif_rawcc + n > tif->tif_rawdatasize)
			n = tif->tif_rawdatasize - tif->tif_rawcc;

		assert( n > 0 );

		/*
		 * Avoid copy if client has setup raw
		 * data buffer to avoid extra copy.
		 */
		if (tif->tif_rawcp != pp)
			_TIFFmemcpy(tif->tif_rawcp, pp, n);
		tif->tif_rawcp += n;
		tif->tif_rawcc += n;
		pp += n;
		cc -= n;
		if (tif->tif_rawcc >= tif->tif_rawdatasize &&
		    !TIFFFlushData1(tif))
			return (0);
	}
	return (1);
}