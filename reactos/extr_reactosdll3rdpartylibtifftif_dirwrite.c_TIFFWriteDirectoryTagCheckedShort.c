#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32 ;
typedef  int /*<<< orphan*/  uint16 ;
struct TYPE_4__ {int tif_flags; } ;
typedef  int /*<<< orphan*/  TIFFDirEntry ;
typedef  TYPE_1__ TIFF ;

/* Variables and functions */
 int /*<<< orphan*/  TIFFSwabShort (int /*<<< orphan*/ *) ; 
 int TIFFWriteDirectoryTagData (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TIFF_SHORT ; 
 int TIFF_SWAB ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static int
TIFFWriteDirectoryTagCheckedShort(TIFF* tif, uint32* ndir, TIFFDirEntry* dir, uint16 tag, uint16 value)
{
	uint16 m;
	assert(sizeof(uint16)==2);
	m=value;
	if (tif->tif_flags&TIFF_SWAB)
		TIFFSwabShort(&m);
	return(TIFFWriteDirectoryTagData(tif,ndir,dir,tag,TIFF_SHORT,1,2,&m));
}