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
typedef  int /*<<< orphan*/  uint16 ;
struct TYPE_8__ {int tif_flags; } ;
struct TYPE_6__ {int /*<<< orphan*/  toff_short; } ;
struct TYPE_7__ {TYPE_1__ tdir_offset; } ;
typedef  TYPE_2__ TIFFDirEntry ;
typedef  TYPE_3__ TIFF ;

/* Variables and functions */
 int /*<<< orphan*/  TIFFSwabShort (int /*<<< orphan*/ *) ; 
 int TIFF_SWAB ; 

__attribute__((used)) static void TIFFReadDirEntryCheckedShort(TIFF* tif, TIFFDirEntry* direntry, uint16* value)
{
	*value = direntry->tdir_offset.toff_short;
	/* *value=*(uint16*)(&direntry->tdir_offset); */
	if (tif->tif_flags&TIFF_SWAB)
		TIFFSwabShort(value);
}