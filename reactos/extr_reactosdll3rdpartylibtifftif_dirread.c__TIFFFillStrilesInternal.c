#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  TIFF ;

/* Variables and functions */

__attribute__((used)) static int _TIFFFillStrilesInternal( TIFF *tif, int loadStripByteCount )
{
#if defined(DEFER_STRILE_LOAD)
        register TIFFDirectory *td = &tif->tif_dir;
        int return_value = 1;

        if( td->td_stripoffset != NULL )
                return 1;

        if( td->td_stripoffset_entry.tdir_count == 0 )
                return 0;

        if (!TIFFFetchStripThing(tif,&(td->td_stripoffset_entry),
                                 td->td_nstrips,&td->td_stripoffset))
        {
                return_value = 0;
        }

        if (loadStripByteCount &&
            !TIFFFetchStripThing(tif,&(td->td_stripbytecount_entry),
                                 td->td_nstrips,&td->td_stripbytecount))
        {
                return_value = 0;
        }

        _TIFFmemset( &(td->td_stripoffset_entry), 0, sizeof(TIFFDirEntry));
        _TIFFmemset( &(td->td_stripbytecount_entry), 0, sizeof(TIFFDirEntry));

	if (tif->tif_dir.td_nstrips > 1 && return_value == 1 ) {
		uint32 strip;

		tif->tif_dir.td_stripbytecountsorted = 1;
		for (strip = 1; strip < tif->tif_dir.td_nstrips; strip++) {
			if (tif->tif_dir.td_stripoffset[strip - 1] >
			    tif->tif_dir.td_stripoffset[strip]) {
				tif->tif_dir.td_stripbytecountsorted = 0;
				break;
			}
		}
	}

        return return_value;
#else /* !defined(DEFER_STRILE_LOAD) */
        (void) tif;
        (void) loadStripByteCount;
        return 1;
#endif 
}