#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64 ;
typedef  scalar_t__ uint16 ;
typedef  enum TIFFReadDirEntryErr { ____Placeholder_TIFFReadDirEntryErr } TIFFReadDirEntryErr ;
struct TYPE_8__ {scalar_t__ td_samplesperpixel; } ;
struct TYPE_10__ {TYPE_1__ tif_dir; } ;
struct TYPE_9__ {scalar_t__ tdir_count; } ;
typedef  TYPE_2__ TIFFDirEntry ;
typedef  TYPE_3__ TIFF ;

/* Variables and functions */
 int TIFFReadDirEntryErrCount ; 
 int TIFFReadDirEntryErrOk ; 
 int TIFFReadDirEntryErrPsdif ; 
 int TIFFReadDirEntryShortArray (TYPE_3__*,TYPE_2__*,scalar_t__**) ; 
 int /*<<< orphan*/  _TIFFfree (scalar_t__*) ; 

__attribute__((used)) static enum TIFFReadDirEntryErr TIFFReadDirEntryPersampleShort(TIFF* tif, TIFFDirEntry* direntry, uint16* value)
{
	enum TIFFReadDirEntryErr err;
	uint16* m;
	uint16* na;
	uint16 nb;
	if (direntry->tdir_count<(uint64)tif->tif_dir.td_samplesperpixel)
		return(TIFFReadDirEntryErrCount);
	err=TIFFReadDirEntryShortArray(tif,direntry,&m);
	if (err!=TIFFReadDirEntryErrOk || m == NULL)
		return(err);
	na=m;
	nb=tif->tif_dir.td_samplesperpixel;
	*value=*na++;
	nb--;
	while (nb>0)
	{
		if (*na++!=*value)
		{
			err=TIFFReadDirEntryErrPsdif;
			break;
		}
		nb--;
	}
	_TIFFfree(m);
	return(err);
}