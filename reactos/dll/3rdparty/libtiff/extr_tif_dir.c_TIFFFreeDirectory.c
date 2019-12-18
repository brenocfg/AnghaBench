#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int td_customValueCount; int /*<<< orphan*/  td_stripbytecount_entry; int /*<<< orphan*/  td_stripoffset_entry; TYPE_1__* td_customValues; int /*<<< orphan*/ * td_fieldsset; } ;
struct TYPE_8__ {TYPE_2__ tif_dir; } ;
struct TYPE_6__ {scalar_t__ value; } ;
typedef  TYPE_2__ TIFFDirectory ;
typedef  int /*<<< orphan*/  TIFFDirEntry ;
typedef  TYPE_3__ TIFF ;

/* Variables and functions */
 int /*<<< orphan*/  CleanupField (int /*<<< orphan*/ ) ; 
 int FIELD_SETLONGS ; 
 int /*<<< orphan*/  FIELD_YCBCRPOSITIONING ; 
 int /*<<< orphan*/  FIELD_YCBCRSUBSAMPLING ; 
 int /*<<< orphan*/  TIFFClrFieldBit (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _TIFFfree (scalar_t__) ; 
 int /*<<< orphan*/  _TIFFmemset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * td_colormap ; 
 int /*<<< orphan*/  td_customValues ; 
 int /*<<< orphan*/  td_inknames ; 
 int /*<<< orphan*/  td_refblackwhite ; 
 int /*<<< orphan*/  td_sampleinfo ; 
 int /*<<< orphan*/  td_smaxsamplevalue ; 
 int /*<<< orphan*/  td_sminsamplevalue ; 
 int /*<<< orphan*/  td_stripbytecount ; 
 int /*<<< orphan*/  td_stripoffset ; 
 int /*<<< orphan*/  td_subifd ; 
 int /*<<< orphan*/ * td_transferfunction ; 

void
TIFFFreeDirectory(TIFF* tif)
{
	TIFFDirectory *td = &tif->tif_dir;
	int            i;

	_TIFFmemset(td->td_fieldsset, 0, FIELD_SETLONGS);
	CleanupField(td_sminsamplevalue);
	CleanupField(td_smaxsamplevalue);
	CleanupField(td_colormap[0]);
	CleanupField(td_colormap[1]);
	CleanupField(td_colormap[2]);
	CleanupField(td_sampleinfo);
	CleanupField(td_subifd);
	CleanupField(td_inknames);
	CleanupField(td_refblackwhite);
	CleanupField(td_transferfunction[0]);
	CleanupField(td_transferfunction[1]);
	CleanupField(td_transferfunction[2]);
	CleanupField(td_stripoffset);
	CleanupField(td_stripbytecount);
	TIFFClrFieldBit(tif, FIELD_YCBCRSUBSAMPLING);
	TIFFClrFieldBit(tif, FIELD_YCBCRPOSITIONING);

	/* Cleanup custom tag values */
	for( i = 0; i < td->td_customValueCount; i++ ) {
		if (td->td_customValues[i].value)
			_TIFFfree(td->td_customValues[i].value);
	}

	td->td_customValueCount = 0;
	CleanupField(td_customValues);

#if defined(DEFER_STRILE_LOAD)
        _TIFFmemset( &(td->td_stripoffset_entry), 0, sizeof(TIFFDirEntry));
        _TIFFmemset( &(td->td_stripbytecount_entry), 0, sizeof(TIFFDirEntry));
#endif        
}