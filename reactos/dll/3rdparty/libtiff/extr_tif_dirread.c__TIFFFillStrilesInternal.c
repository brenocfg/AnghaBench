#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32 ;
struct TYPE_9__ {scalar_t__ tdir_count; } ;
struct TYPE_7__ {scalar_t__* td_stripoffset; int td_nstrips; scalar_t__* td_stripbytecount; int td_stripbytecountsorted; TYPE_3__ td_stripbytecount_entry; TYPE_3__ td_stripoffset_entry; } ;
struct TYPE_8__ {TYPE_1__ tif_dir; } ;
typedef  TYPE_1__ TIFFDirectory ;
typedef  int /*<<< orphan*/  TIFFDirEntry ;
typedef  TYPE_2__ TIFF ;

/* Variables and functions */
 int /*<<< orphan*/  TIFFFetchStripThing (TYPE_2__*,TYPE_3__*,int,scalar_t__**) ; 
 int /*<<< orphan*/  _TIFFmemset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

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