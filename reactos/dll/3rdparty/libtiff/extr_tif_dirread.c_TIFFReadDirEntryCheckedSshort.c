#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16 ;
typedef  int /*<<< orphan*/  int16 ;
struct TYPE_6__ {int tif_flags; } ;
struct TYPE_5__ {int /*<<< orphan*/  tdir_offset; } ;
typedef  TYPE_1__ TIFFDirEntry ;
typedef  TYPE_2__ TIFF ;

/* Variables and functions */
 int /*<<< orphan*/  TIFFSwabShort (int /*<<< orphan*/ *) ; 
 int TIFF_SWAB ; 

__attribute__((used)) static void TIFFReadDirEntryCheckedSshort(TIFF* tif, TIFFDirEntry* direntry, int16* value)
{
	*value=*(int16*)(&direntry->tdir_offset);
	if (tif->tif_flags&TIFF_SWAB)
		TIFFSwabShort((uint16*)value);
}