#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8 ;
typedef  scalar_t__ uint32 ;
typedef  int /*<<< orphan*/  tmsize_t ;
struct TYPE_7__ {scalar_t__ td_nstrips; scalar_t__ td_planarconfig; scalar_t__ td_stripsperimage; scalar_t__ td_rowsperstrip; int /*<<< orphan*/  td_imagelength; } ;
struct TYPE_8__ {scalar_t__ tif_row; int /*<<< orphan*/  tif_clientdata; scalar_t__ tif_curstrip; TYPE_1__ tif_dir; } ;
typedef  TYPE_1__ TIFFDirectory ;
typedef  TYPE_2__ TIFF ;

/* Variables and functions */
 scalar_t__ PLANARCONFIG_SEPARATE ; 
 scalar_t__ TIFFAppendToStrip (TYPE_2__*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TIFFErrorExt (int /*<<< orphan*/ ,char const*,char*) ; 
 int /*<<< orphan*/  TIFFGrowStrips (TYPE_2__*,int,char const*) ; 
 scalar_t__ TIFFhowmany_32 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  WRITECHECKSTRIPS (TYPE_2__*,char const*) ; 

tmsize_t
TIFFWriteRawStrip(TIFF* tif, uint32 strip, void* data, tmsize_t cc)
{
	static const char module[] = "TIFFWriteRawStrip";
	TIFFDirectory *td = &tif->tif_dir;

	if (!WRITECHECKSTRIPS(tif, module))
		return ((tmsize_t) -1);
	/*
	 * Check strip array to make sure there's space.
	 * We don't support dynamically growing files that
	 * have data organized in separate bitplanes because
	 * it's too painful.  In that case we require that
	 * the imagelength be set properly before the first
	 * write (so that the strips array will be fully
	 * allocated above).
	 */
	if (strip >= td->td_nstrips) {
		if (td->td_planarconfig == PLANARCONFIG_SEPARATE) {
			TIFFErrorExt(tif->tif_clientdata, module,
			    "Can not grow image by strips when using separate planes");
			return ((tmsize_t) -1);
		}
		/*
		 * Watch out for a growing image.  The value of
		 * strips/image will initially be 1 (since it
		 * can't be deduced until the imagelength is known).
		 */
		if (strip >= td->td_stripsperimage)
			td->td_stripsperimage =
			    TIFFhowmany_32(td->td_imagelength,td->td_rowsperstrip);
		if (!TIFFGrowStrips(tif, 1, module))
			return ((tmsize_t) -1);
	}
	tif->tif_curstrip = strip;
        if (td->td_stripsperimage == 0) {
                TIFFErrorExt(tif->tif_clientdata, module,"Zero strips per image");
                return ((tmsize_t) -1);
        }
	tif->tif_row = (strip % td->td_stripsperimage) * td->td_rowsperstrip;
	return (TIFFAppendToStrip(tif, strip, (uint8*) data, cc) ?
	    cc : (tmsize_t) -1);
}