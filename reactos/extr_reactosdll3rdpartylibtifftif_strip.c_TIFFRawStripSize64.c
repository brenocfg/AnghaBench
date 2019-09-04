#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64 ;
typedef  size_t uint32 ;
struct TYPE_4__ {scalar_t__* td_stripbytecount; } ;
struct TYPE_5__ {int /*<<< orphan*/  tif_clientdata; TYPE_1__ tif_dir; } ;
typedef  TYPE_1__ TIFFDirectory ;
typedef  TYPE_2__ TIFF ;

/* Variables and functions */
 int /*<<< orphan*/  TIFFErrorExt (int /*<<< orphan*/ ,char const*,char*,unsigned long long,unsigned long) ; 

uint64
TIFFRawStripSize64(TIFF* tif, uint32 strip)
{
	static const char module[] = "TIFFRawStripSize64";
	TIFFDirectory* td = &tif->tif_dir;
	uint64 bytecount = td->td_stripbytecount[strip];

	if (bytecount == 0)
	{
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
		bytecount = (uint64) -1;
	}

	return bytecount;
}