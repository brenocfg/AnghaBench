#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64 ;
typedef  int /*<<< orphan*/  uint32 ;
typedef  enum TIFFReadDirEntryErr { ____Placeholder_TIFFReadDirEntryErr } TIFFReadDirEntryErr ;
struct TYPE_5__ {int tdir_count; int tdir_type; } ;
typedef  TYPE_1__ TIFFDirEntry ;
typedef  int /*<<< orphan*/  TIFF ;

/* Variables and functions */
 int /*<<< orphan*/  TIFFReadDirEntryCheckedLong (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int TIFFReadDirEntryCheckedLong8 (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int TIFFReadDirEntryErrCount ; 
 int TIFFReadDirEntryErrOk ; 
 int TIFFReadDirEntryErrType ; 
#define  TIFF_IFD 131 
#define  TIFF_IFD8 130 
#define  TIFF_LONG 129 
#define  TIFF_LONG8 128 

__attribute__((used)) static enum TIFFReadDirEntryErr TIFFReadDirEntryIfd8(TIFF* tif, TIFFDirEntry* direntry, uint64* value)
{
	enum TIFFReadDirEntryErr err;
	if (direntry->tdir_count!=1)
		return(TIFFReadDirEntryErrCount);
	switch (direntry->tdir_type)
	{
		case TIFF_LONG:
		case TIFF_IFD:
			{
				uint32 m;
				TIFFReadDirEntryCheckedLong(tif,direntry,&m);
				*value=(uint64)m;
				return(TIFFReadDirEntryErrOk);
			}
		case TIFF_LONG8:
		case TIFF_IFD8:
			err=TIFFReadDirEntryCheckedLong8(tif,direntry,value);
			return(err);
		default:
			return(TIFFReadDirEntryErrType);
	}
}