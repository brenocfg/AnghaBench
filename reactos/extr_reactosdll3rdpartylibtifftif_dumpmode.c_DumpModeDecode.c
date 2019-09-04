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
typedef  int /*<<< orphan*/  uint16 ;
typedef  scalar_t__ tmsize_t ;
struct TYPE_3__ {scalar_t__ tif_rawcc; int /*<<< orphan*/ * tif_rawcp; scalar_t__ tif_row; int /*<<< orphan*/  tif_clientdata; } ;
typedef  TYPE_1__ TIFF ;

/* Variables and functions */
 int /*<<< orphan*/  TIFFErrorExt (int /*<<< orphan*/ ,char const*,char*,unsigned long,long long,long long) ; 
 int /*<<< orphan*/  _TIFFmemcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static int
DumpModeDecode(TIFF* tif, uint8* buf, tmsize_t cc, uint16 s)
{
	static const char module[] = "DumpModeDecode";
	(void) s;
	if (tif->tif_rawcc < cc) {
#if defined(__WIN32__) && (defined(_MSC_VER) || defined(__MINGW32__))
		TIFFErrorExt(tif->tif_clientdata, module,
"Not enough data for scanline %lu, expected a request for at most %I64d bytes, got a request for %I64d bytes",
		             (unsigned long) tif->tif_row,
		             (signed __int64) tif->tif_rawcc,
		             (signed __int64) cc);
#else
		TIFFErrorExt(tif->tif_clientdata, module,
"Not enough data for scanline %lu, expected a request for at most %lld bytes, got a request for %lld bytes",
		             (unsigned long) tif->tif_row,
		             (signed long long) tif->tif_rawcc,
		             (signed long long) cc);
#endif
		return (0);
	}
	/*
	 * Avoid copy if client has setup raw
	 * data buffer to avoid extra copy.
	 */
	if (tif->tif_rawcp != buf)
		_TIFFmemcpy(buf, tif->tif_rawcp, cc);
	tif->tif_rawcp += cc;
	tif->tif_rawcc -= cc;  
	return (1);
}