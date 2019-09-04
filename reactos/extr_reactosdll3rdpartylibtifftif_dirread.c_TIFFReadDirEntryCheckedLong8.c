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
typedef  int /*<<< orphan*/  uint64 ;
typedef  int /*<<< orphan*/  uint32 ;
typedef  enum TIFFReadDirEntryErr { ____Placeholder_TIFFReadDirEntryErr } TIFFReadDirEntryErr ;
struct TYPE_9__ {int tif_flags; } ;
struct TYPE_7__ {int /*<<< orphan*/  toff_long8; int /*<<< orphan*/  toff_long; } ;
struct TYPE_8__ {TYPE_1__ tdir_offset; } ;
typedef  TYPE_2__ TIFFDirEntry ;
typedef  TYPE_3__ TIFF ;

/* Variables and functions */
 int TIFFReadDirEntryData (TYPE_3__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int TIFFReadDirEntryErrOk ; 
 int /*<<< orphan*/  TIFFSwabLong (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TIFFSwabLong8 (int /*<<< orphan*/ *) ; 
 int TIFF_BIGTIFF ; 
 int TIFF_SWAB ; 

__attribute__((used)) static enum TIFFReadDirEntryErr TIFFReadDirEntryCheckedLong8(TIFF* tif, TIFFDirEntry* direntry, uint64* value)
{
	if (!(tif->tif_flags&TIFF_BIGTIFF))
	{
		enum TIFFReadDirEntryErr err;
		uint32 offset = direntry->tdir_offset.toff_long;
		if (tif->tif_flags&TIFF_SWAB)
			TIFFSwabLong(&offset);
		err=TIFFReadDirEntryData(tif,offset,8,value);
		if (err!=TIFFReadDirEntryErrOk)
			return(err);
	}
	else
		*value = direntry->tdir_offset.toff_long8;
	if (tif->tif_flags&TIFF_SWAB)
		TIFFSwabLong8(value);
	return(TIFFReadDirEntryErrOk);
}