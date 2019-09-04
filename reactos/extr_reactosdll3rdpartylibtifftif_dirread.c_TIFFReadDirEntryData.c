#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64 ;
typedef  scalar_t__ tmsize_t ;
typedef  enum TIFFReadDirEntryErr { ____Placeholder_TIFFReadDirEntryErr } TIFFReadDirEntryErr ;
struct TYPE_6__ {scalar_t__ tif_base; scalar_t__ tif_size; } ;
typedef  TYPE_1__ TIFF ;

/* Variables and functions */
 int /*<<< orphan*/  ReadOK (TYPE_1__*,void*,scalar_t__) ; 
 int /*<<< orphan*/  SeekOK (TYPE_1__*,scalar_t__) ; 
 int TIFFReadDirEntryErrIo ; 
 int TIFFReadDirEntryErrOk ; 
 int /*<<< orphan*/  _TIFFmemcpy (void*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  isMapped (TYPE_1__*) ; 

__attribute__((used)) static enum TIFFReadDirEntryErr
TIFFReadDirEntryData(TIFF* tif, uint64 offset, tmsize_t size, void* dest)
{
	assert(size>0);
	if (!isMapped(tif)) {
		if (!SeekOK(tif,offset))
			return(TIFFReadDirEntryErrIo);
		if (!ReadOK(tif,dest,size))
			return(TIFFReadDirEntryErrIo);
	} else {
		size_t ma,mb;
		ma=(size_t)offset;
		mb=ma+size;
		if (((uint64)ma!=offset)
		    || (mb < ma)
		    || (mb - ma != (size_t) size)
		    || (mb < (size_t)size)
		    || (mb > (size_t)tif->tif_size)
		    )
			return(TIFFReadDirEntryErrIo);
		_TIFFmemcpy(dest,tif->tif_base+ma,size);
	}
	return(TIFFReadDirEntryErrOk);
}