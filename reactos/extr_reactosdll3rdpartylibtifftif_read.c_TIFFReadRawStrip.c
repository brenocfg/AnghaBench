#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64 ;
typedef  size_t uint32 ;
typedef  scalar_t__ tmsize_t ;
typedef  scalar_t__ int64 ;
struct TYPE_6__ {size_t td_nstrips; scalar_t__* td_stripbytecount; } ;
struct TYPE_7__ {int tif_flags; int /*<<< orphan*/  tif_clientdata; TYPE_1__ tif_dir; } ;
typedef  TYPE_1__ TIFFDirectory ;
typedef  TYPE_2__ TIFF ;

/* Variables and functions */
 int /*<<< orphan*/  TIFFCheckRead (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TIFFErrorExt (int /*<<< orphan*/ ,char const*,char*,...) ; 
 scalar_t__ TIFFReadRawStrip1 (TYPE_2__*,size_t,void*,scalar_t__,char const*) ; 
 int TIFF_NOREADRAW ; 

tmsize_t
TIFFReadRawStrip(TIFF* tif, uint32 strip, void* buf, tmsize_t size)
{
	static const char module[] = "TIFFReadRawStrip";
	TIFFDirectory *td = &tif->tif_dir;
	uint64 bytecount;
	tmsize_t bytecountm;

	if (!TIFFCheckRead(tif, 0))
		return ((tmsize_t)(-1));
	if (strip >= td->td_nstrips) {
		TIFFErrorExt(tif->tif_clientdata, module,
		     "%lu: Strip out of range, max %lu",
		     (unsigned long) strip,
		     (unsigned long) td->td_nstrips);
		return ((tmsize_t)(-1));
	}
	if (tif->tif_flags&TIFF_NOREADRAW)
	{
		TIFFErrorExt(tif->tif_clientdata, module,
		    "Compression scheme does not support access to raw uncompressed data");
		return ((tmsize_t)(-1));
	}
	bytecount = td->td_stripbytecount[strip];
	if ((int64)bytecount <= 0) {
#if defined(__WIN32__) && (defined(_MSC_VER) || defined(__MINGW32__))
		TIFFErrorExt(tif->tif_clientdata, module,
			     "%I64u: Invalid strip byte count, strip %lu",
			     (unsigned __int64) bytecount,
			     (unsigned long) strip);
#else
		TIFFErrorExt(tif->tif_clientdata, module,
			     "%llu: Invalid strip byte count, strip %lu",
			     (unsigned long long) bytecount,
			     (unsigned long) strip);
#endif
		return ((tmsize_t)(-1));
	}
	bytecountm = (tmsize_t)bytecount;
	if ((uint64)bytecountm!=bytecount) {
		TIFFErrorExt(tif->tif_clientdata, module, "Integer overflow");
		return ((tmsize_t)(-1));
	}
	if (size != (tmsize_t)(-1) && size < bytecountm)
		bytecountm = size;
	return (TIFFReadRawStrip1(tif, strip, buf, bytecountm, module));
}