#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64 ;
typedef  size_t uint32 ;
typedef  scalar_t__ tmsize_t ;
struct TYPE_8__ {scalar_t__* td_stripoffset; } ;
struct TYPE_9__ {int tif_flags; scalar_t__ tif_size; scalar_t__ tif_base; scalar_t__ tif_col; scalar_t__ tif_row; int /*<<< orphan*/  tif_clientdata; TYPE_1__ tif_dir; } ;
typedef  TYPE_1__ TIFFDirectory ;
typedef  TYPE_2__ TIFF ;

/* Variables and functions */
 int /*<<< orphan*/  SeekOK (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  TIFFErrorExt (int /*<<< orphan*/ ,char const*,char*,unsigned long,unsigned long,unsigned long,...) ; 
 scalar_t__ TIFFReadFile (TYPE_2__*,void*,scalar_t__) ; 
 int TIFF_NOREADRAW ; 
 scalar_t__ TIFF_TMSIZE_T_MAX ; 
 int /*<<< orphan*/  _TIFFFillStriles (TYPE_2__*) ; 
 int /*<<< orphan*/  _TIFFmemcpy (void*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  isMapped (TYPE_2__*) ; 

__attribute__((used)) static tmsize_t
TIFFReadRawTile1(TIFF* tif, uint32 tile, void* buf, tmsize_t size, const char* module)
{
	TIFFDirectory *td = &tif->tif_dir;

    if (!_TIFFFillStriles( tif ))
        return ((tmsize_t)(-1));

	assert((tif->tif_flags&TIFF_NOREADRAW)==0);
	if (!isMapped(tif)) {
		tmsize_t cc;

		if (!SeekOK(tif, td->td_stripoffset[tile])) {
			TIFFErrorExt(tif->tif_clientdata, module,
			    "Seek error at row %lu, col %lu, tile %lu",
			    (unsigned long) tif->tif_row,
			    (unsigned long) tif->tif_col,
			    (unsigned long) tile);
			return ((tmsize_t)(-1));
		}
		cc = TIFFReadFile(tif, buf, size);
		if (cc != size) {
#if defined(__WIN32__) && (defined(_MSC_VER) || defined(__MINGW32__))
			TIFFErrorExt(tif->tif_clientdata, module,
	"Read error at row %lu, col %lu; got %I64u bytes, expected %I64u",
				     (unsigned long) tif->tif_row,
				     (unsigned long) tif->tif_col,
				     (unsigned __int64) cc,
				     (unsigned __int64) size);
#else
			TIFFErrorExt(tif->tif_clientdata, module,
	"Read error at row %lu, col %lu; got %llu bytes, expected %llu",
				     (unsigned long) tif->tif_row,
				     (unsigned long) tif->tif_col,
				     (unsigned long long) cc,
				     (unsigned long long) size);
#endif
			return ((tmsize_t)(-1));
		}
	} else {
		tmsize_t ma,mb;
		tmsize_t n;
		ma=(tmsize_t)td->td_stripoffset[tile];
		mb=ma+size;
		if ((td->td_stripoffset[tile] > (uint64)TIFF_TMSIZE_T_MAX)||(ma>tif->tif_size))
			n=0;
		else if ((mb<ma)||(mb<size)||(mb>tif->tif_size))
			n=tif->tif_size-ma;
		else
			n=size;
		if (n!=size) {
#if defined(__WIN32__) && (defined(_MSC_VER) || defined(__MINGW32__))
			TIFFErrorExt(tif->tif_clientdata, module,
"Read error at row %lu, col %lu, tile %lu; got %I64u bytes, expected %I64u",
				     (unsigned long) tif->tif_row,
				     (unsigned long) tif->tif_col,
				     (unsigned long) tile,
				     (unsigned __int64) n,
				     (unsigned __int64) size);
#else
			TIFFErrorExt(tif->tif_clientdata, module,
"Read error at row %lu, col %lu, tile %lu; got %llu bytes, expected %llu",
				     (unsigned long) tif->tif_row,
				     (unsigned long) tif->tif_col,
				     (unsigned long) tile,
				     (unsigned long long) n,
				     (unsigned long long) size);
#endif
			return ((tmsize_t)(-1));
		}
		_TIFFmemcpy(buf, tif->tif_base + ma, size);
	}
	return (size);
}