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
typedef  int /*<<< orphan*/  uint64 ;
typedef  int uint32 ;
typedef  enum TIFFReadDirEntryErr { ____Placeholder_TIFFReadDirEntryErr } TIFFReadDirEntryErr ;
struct TYPE_8__ {int tif_flags; } ;
struct TYPE_7__ {int tdir_type; } ;
typedef  TYPE_1__ TIFFDirEntry ;
typedef  TYPE_2__ TIFF ;

/* Variables and functions */
 int TIFFReadDirEntryArray (TYPE_2__*,TYPE_1__*,int*,int,void**) ; 
 int TIFFReadDirEntryErrAlloc ; 
 int TIFFReadDirEntryErrOk ; 
 int TIFFReadDirEntryErrType ; 
 int /*<<< orphan*/  TIFFSwabArrayOfLong8 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TIFFSwabLong (int*) ; 
#define  TIFF_IFD 131 
#define  TIFF_IFD8 130 
#define  TIFF_LONG 129 
#define  TIFF_LONG8 128 
 int TIFF_SWAB ; 
 int /*<<< orphan*/  _TIFFfree (void*) ; 
 scalar_t__ _TIFFmalloc (int) ; 

__attribute__((used)) static enum TIFFReadDirEntryErr TIFFReadDirEntryIfd8Array(TIFF* tif, TIFFDirEntry* direntry, uint64** value)
{
	enum TIFFReadDirEntryErr err;
	uint32 count;
	void* origdata;
	uint64* data;
	switch (direntry->tdir_type)
	{
		case TIFF_LONG:
		case TIFF_LONG8:
		case TIFF_IFD:
		case TIFF_IFD8:
			break;
		default:
			return(TIFFReadDirEntryErrType);
	}
	err=TIFFReadDirEntryArray(tif,direntry,&count,8,&origdata);
	if ((err!=TIFFReadDirEntryErrOk)||(origdata==0))
	{
		*value=0;
		return(err);
	}
	switch (direntry->tdir_type)
	{
		case TIFF_LONG8:
		case TIFF_IFD8:
			*value=(uint64*)origdata;
			if (tif->tif_flags&TIFF_SWAB)
				TIFFSwabArrayOfLong8(*value,count);
			return(TIFFReadDirEntryErrOk);
	}
	data=(uint64*)_TIFFmalloc(count*8);
	if (data==0)
	{
		_TIFFfree(origdata);
		return(TIFFReadDirEntryErrAlloc);
	}
	switch (direntry->tdir_type)
	{
		case TIFF_LONG:
		case TIFF_IFD:
			{
				uint32* ma;
				uint64* mb;
				uint32 n;
				ma=(uint32*)origdata;
				mb=data;
				for (n=0; n<count; n++)
				{
					if (tif->tif_flags&TIFF_SWAB)
						TIFFSwabLong(ma);
					*mb++=(uint64)(*ma++);
				}
			}
			break;
	}
	_TIFFfree(origdata);
	*value=data;
	return(TIFFReadDirEntryErrOk);
}